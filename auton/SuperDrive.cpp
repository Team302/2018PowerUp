/*
 * SuperDrive.cpp
 *
 *  Created on: Jan 18, 2018
 *      Author: jonah
 */

#include <auton/SuperDrive.h>
#include <factories/ChassisFactory.h>
#include <cmath>
#include <SmartDashboard/SmartDashboard.h>

SuperDrive::SuperDrive() :
	m_chassis(ChassisFactory::GetIChassis()),
	m_targetSpeed(0),
	m_currentSpeed(0),
	m_speedOffset(0),
	m_leftSpeed(0),
	m_rightSpeed(0),
	m_currentHeading(0),
	m_startHeading(0),
	m_slowingDown(false),
	m_reachedTargetSpeed(false),
	m_accelDecelTime(0),
	m_currentTime(0),
	m_minSpeedSlowdown(0)
{
}

void SuperDrive::Init(PrimitiveParams* params) {
//	m_chassis->SetTalonMode(DragonTalon::PERCENT); //TODO: get velocity working
	m_chassis->SetTalonMode(DragonTalon::VELOCITY);
//	m_chassis->SetTalonMode(DragonTalon::MAGIC_MOTION);
	m_targetSpeed = params->GetDriveSpeed();
	m_leftSpeed = params->GetDriveSpeed();
	m_rightSpeed = params->GetDriveSpeed();

	if (params->GetEndDriveSpeed() > MIN_SPEED_SLOWDOWN) {
		m_minSpeedSlowdown = params->GetEndDriveSpeed();
	} else {
		m_minSpeedSlowdown = MIN_SPEED_SLOWDOWN;
	}

	//Reset some variables
	m_currentTime = 0;
	m_slowingDown = false;
	m_reachedTargetSpeed = false;
	m_accelDecelTime = 0;

	m_currentSpeed = m_chassis->GetVelocity();
	//Double check that the current speed matches the sign of the target speed (if not, thats bad. make it 0)
	if (m_targetSpeed > 0) {
		if (m_currentSpeed < 0) {
			m_currentSpeed = 0;
		}
	} else { //target speed negative
		if (m_currentSpeed > 0) {
			m_currentSpeed = 0;
		}
	}

	m_startHeading = m_chassis->GetHeading();
    m_chassis->SetVelocityParams(PROPORTIONAL_COEFF, INTREGRAL_COEFF, DERIVATIVE_COEFF, FEET_FORWARD_COEFF,
    		m_leftSpeed, m_rightSpeed);

    m_speedOffset = m_targetSpeed > 0.0 ? GYRO_CORRECTION_CONSTANT : -GYRO_CORRECTION_CONSTANT;
}

void SuperDrive::Run() {
	m_currentHeading = m_chassis->GetHeading() - m_chassis->GetTargetHeading(); //Calculate target heading
	frc::SmartDashboard::PutNumber("Current target heading drive", ChassisFactory::GetIChassis()->GetTargetHeading());

	//Calculate ramp up speed if we are not already slowing down
	if (!m_slowingDown) {
//		printf("speeding up\n");
		if (std::abs(m_currentSpeed) < std::abs(m_targetSpeed)) {
			if (m_targetSpeed > 0) {
				m_currentSpeed += INCHES_PER_SECOND_SECOND * IPrimitive::LOOP_LENGTH;
			} else {
				m_currentSpeed -= INCHES_PER_SECOND_SECOND * IPrimitive::LOOP_LENGTH;
			}
		} else {
			m_currentSpeed = m_targetSpeed;
			if (!m_reachedTargetSpeed)
				m_accelDecelTime = m_currentTime;
			m_reachedTargetSpeed = true;
		}
	} else {
		if (!m_reachedTargetSpeed)
			m_accelDecelTime = m_currentTime;
		m_reachedTargetSpeed = true;

		if (m_currentSpeed > 0) {
			if (m_currentSpeed > m_minSpeedSlowdown) {
				m_currentSpeed -= INCHES_PER_SECOND_SECOND * IPrimitive::LOOP_LENGTH;
			} else {
				m_currentSpeed = m_minSpeedSlowdown;
			}
		} else {
			//current speed is negative
			if (m_currentSpeed < -m_minSpeedSlowdown) {
				m_currentSpeed += INCHES_PER_SECOND_SECOND * IPrimitive::LOOP_LENGTH;
			} else {
				m_currentSpeed = -m_minSpeedSlowdown;
			}
		}
	}


	m_rightSpeed = m_currentSpeed;
	m_leftSpeed = m_currentSpeed;

	m_leftSpeed -= m_currentHeading * GYRO_CORRECTION_CONSTANT;
	m_rightSpeed += m_currentHeading * GYRO_CORRECTION_CONSTANT;

	frc::SmartDashboard::PutNumber("SuperDrive Left speed", m_leftSpeed);
	frc::SmartDashboard::PutNumber("SuperDrive right speed", m_rightSpeed);

	m_chassis->SetVelocityParams(PROPORTIONAL_COEFF, INTREGRAL_COEFF, DERIVATIVE_COEFF, FEET_FORWARD_COEFF, m_leftSpeed, m_rightSpeed);

	m_currentTime += IPrimitive::LOOP_LENGTH;


	//printing stuff
//	frc::SmartDashboard::PutNumber("DriveDist target velocity", m_currentSpeed);
//	frc::SmartDashboard::PutNumber("DriveDist actual velocity", ChassisFactory::GetIChassis()->GetVelocity());
}

bool SuperDrive::IsDone() {
	return false;
	//if u don't override this im gonna be mad
}

void SuperDrive::SlowDown() {
//	printf("Slow down\n");
	m_slowingDown = true;
}

bool SuperDrive::ReachedTargetSpeed() {
	return m_reachedTargetSpeed;
}

//float SuperDrive::GetAccelDecelTime() { //TODO: unused method. remove
//	return m_accelDecelTime * DECEL_TIME_MULTIPLIER; //multiplier reduces the amount of time we are decelerating
//}
