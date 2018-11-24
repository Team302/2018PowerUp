/*
 * TurnAngle.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

//Includes
#include <cmath>
#include <SmartDashboard/SmartDashboard.h>
//Team302 includes
#include <auton/TurnAngle.h>
#include <factories/ChassisFactory.h>
#include <auton/PrimitiveFactory.h>
#include <interfaces/IChassis.h>
#include <utils/LimitValue.h>

TurnAngle::TurnAngle() :
		m_chassis(ChassisFactory::GetIChassis()),
		m_lift(new LiftElevator),
		m_targetAngle(0.0),
		m_maxTimeout(0.0),
		m_leftPos(0.0),
		m_rightPos(0.0),
		m_isDone(false)
{
}

void TurnAngle::Init(PrimitiveParams* params) {
	m_isDone = false;
	m_chassis->SetTalonMode(DragonTalon::POSITION); 													//Set the talon mode to position
	m_targetAngle = m_chassis->GetTargetHeading() + params->GetHeading();								//Set the target angle to the current angle plus the heading param
	m_chassis->SetTargetHeading(m_targetAngle);															//Set the internal chassis target heading to the target heading

	m_leftPos = m_chassis->GetLeftMasterMotorRotationCount();											//init left and right position to the current wheel positions
	m_rightPos = m_chassis->GetRightMasterMotorRotationCount();

	m_maxTimeout = 99999;																					//Initialize the

	m_chassis->SetPIDParams(PROPORTIONAL_COEFF, INTREGRAL_COEFF, DERIVATIVE_COEFF, FEET_FORWARD_COEFF); //Set parameters
	m_lift->Init(params);																				//Init the lift parallel primitive
}

void TurnAngle::Run() //best method ever. Does nothing, and should do nothing... NOT ANYMORE, BUDDY!
{
	float deltaAngle = m_targetAngle - m_chassis->GetHeading();
	float velocity = deltaAngle * ANGLE_DIFFERENCE_VELOCITY_MULTIPLIER;
	bool sign = velocity > 0;	//Store sign of velocity as positive = true
	velocity = LimitValue::ForceInRange(std::abs(velocity), MIN_VELOCITY, MAX_VELOCITY);
	if (!sign) { 				//If the sign was negative...
		velocity = -velocity; 	//... make it negative again :)
	}

	m_leftPos  += (velocity * 0.02) / (m_chassis->GetWheelDiameter() * M_PI);
	m_rightPos -= (velocity * 0.02) / (m_chassis->GetWheelDiameter() * M_PI);

//	m_chassis->SetDriveMagnitudes(m_leftPos, m_rightPos);
	m_chassis->SetLeftRightMagnitudes(m_leftPos, m_rightPos);

	m_lift->Run();
	m_maxTimeout -= IPrimitive::LOOP_LENGTH;
}

bool TurnAngle::IsDone() {
	if (!m_isDone) {
		float absDeltaAngle = std::abs(m_targetAngle - m_chassis->GetHeading());
		if (absDeltaAngle < ANGLE_THRESH) {
			m_isDone = true;
			m_chassis->SetTalonMode(DragonTalon::PERCENT);
			m_chassis->SetLeftRightMagnitudes(0, 0);
		}
	}
	return m_isDone || m_maxTimeout < (IPrimitive::LOOP_LENGTH / 2);
}
