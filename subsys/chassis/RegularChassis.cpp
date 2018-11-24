/*
 * RegularChassis.cpp
 *
 *  Created on: Dec 20, 2017
 *      Author: jonah
 */

//includes
#include <iostream>
#include <cmath>
#include <vector>
#include <SmartDashboard/SmartDashboard.h>

//team302 includes
#include <utils/DragonMath.h>
#include <subsys/chassis/RegularChassis.h>
#include <subsys/components/DragonNavX.h>
#include <subsys/components/DragonNavXLogoBack.h>

RegularChassis::RegularChassis(float wheelDiameter,	// <I> - Diameter of the wheel in inches
		float wheelBase,	// <I> - Front-Back distance between wheel centers
		float track,	// <I> - Left-Right distance between wheels (same axle)
		std::vector<DragonTalon*> motorControllers	// <I> - Motor Controllers
		) :
		IChassis(),
		m_navx( new DragonNavXLogoBack(DragonNavX::NAVX_PORT_TYPE::SPI, 0, 200)), //TODO: double check if an update rate of 200 is working and is beneficial
                m_pigeon(DragonPigeon::GetPigeon()), 
		m_frontLeftMotor(),
		m_frontRightMotor(),
		m_backLeftMotor(),
		m_backRightMotor(),
		m_location(	{ 0, 0 }),
		m_resetHeading(0),
		m_targetHeading(0),
		m_pDistance(0),
		m_pathTravelVelocityTarget(0),
		m_wheelDiameter( wheelDiameter),
		m_wheelBase(wheelBase),
		m_track(track),
		velocityToRPM( 60.0 / (wheelDiameter * M_PI)), // ips * this = rpm. rpm / this = ips
		m_periodicMSGWritten( false )

{
	for (unsigned int inx = 0; inx < motorControllers.size(); ++inx) {
//		printf("==>> motor controller [ %d ] = %d \n", inx,
//				motorControllers[inx]->GetType());
		switch (motorControllers[inx]->GetType()) {
		case DragonTalon::TALON_TYPE::TANK_LEFT_MASTER:
			m_backLeftMotor = motorControllers[inx];
			break;

		case DragonTalon::TALON_TYPE::TANK_LEFT_SLAVE1:
			m_frontLeftMotor = motorControllers[inx];
			break;

		case DragonTalon::TALON_TYPE::TANK_RIGHT_MASTER:
			m_backRightMotor = motorControllers[inx];
			break;

		case DragonTalon::TALON_TYPE::TANK_RIGHT_SLAVE1:
			m_frontRightMotor = motorControllers[inx];
			break;

		default:
			printf("==>> RegularChassis:  Invalid Motor %d \n",
					motorControllers[inx]->GetType());
			break;
		}
	}
}

RegularChassis::~RegularChassis() {
	delete m_frontLeftMotor;
	delete m_frontRightMotor;
	delete m_backLeftMotor;
	delete m_backRightMotor;
}

double RegularChassis::GetWheelDiameter() const {
	return m_wheelDiameter;
}

double RegularChassis::GetLeftMasterMotorRotationCount() const {
	return m_backLeftMotor->GetRotationCount();
}

double RegularChassis::GetRightMasterMotorRotationCount() const {
	return m_backRightMotor->GetRotationCount();
}

//i tried to refactor GetVelocity to GetTotalVelocity and eclipse crashed so now im mad
double RegularChassis::GetVelocity() const {
	return GetYVelocity();
}

double RegularChassis::GetXVelocity() const {
	return 0; //Always 0 in regular chassis unless we calculate drift in omnis
}

double RegularChassis::GetYVelocity() const {
	//Average left and right velocity to get total Y velocity
	return (GetLeftVelocity() + GetRightVelocity()) / 2.0;
}

double RegularChassis::GetDistance() const {
	//We want to use the encoders with the most distance per side, so we compare the left encoders to find the one that is furthest from 0 and save it as a double.
	//Do the same for the right and then average the two and return it as the robots distance.
//	double left = GetBestOfTwo(m_frontLeftMotor->GetRotationCount(),
//			m_backLeftMotor->GetRotationCount());
//	double right = GetBestOfTwo(m_frontRightMotor->GetRotationCount(),
//			m_backRightMotor->GetRotationCount());

	//BIG TODO: change how get distance works so that get best of two gets the best of velocity instead of absolute encoder distance.
	//this requires a new getbestoftwo that returns a boolean describing which one is the best of two, and then we can tell which distance to use.
	double left = m_backLeftMotor->GetRotationCount();
	double right = m_backRightMotor->GetRotationCount();

	frc::SmartDashboard::PutNumber("best left enc: ", left);
	frc::SmartDashboard::PutNumber("best right enc: ", right);

	return ((left + right) / 2.0) * m_wheelDiameter * M_PI;
}

double RegularChassis::GetXLocation() const {
	return m_location.x;
}

double RegularChassis::GetYLocation() const {
	return m_location.y;
}

double RegularChassis::GetHeading() const {
//	if (m_navx == nullptr) {
//		printf("WARNING: navx is NULLPTR!");
//		return -1;
//	} else {
////		return m_navx->GetFusedHeading();
//		return m_navx->GetAngle();
////		return m_navx->GetAltitude();
//	}
	if (m_pigeon == nullptr )
	{
	    if ( !m_periodicMSGWritten )
	    {
//	        printf("WARNING: pigeon is NULLPTR! \n");
	        m_periodicMSGWritten = true;
	    }
		return -1;
	}
	else
	{
		return -(m_pigeon->GetFusedHeading() - m_resetHeading); //negative because we are using + is clockwise
	}
}

void RegularChassis::EnableBrakeMode(bool enabled) {
	if (enabled) {
//		m_frontLeftMotor->SetNeutralMode(NeutralMode::Brake);
//		m_frontRightMotor->SetNeutralMode(NeutralMode::Brake);
		m_backLeftMotor->SetNeutralMode(NeutralMode::Brake);
		m_backRightMotor->SetNeutralMode(NeutralMode::Brake);
	} else {
//		m_frontLeftMotor->SetNeutralMode(NeutralMode::Coast);
//		m_frontRightMotor->SetNeutralMode(NeutralMode::Coast);
		m_backLeftMotor->SetNeutralMode(NeutralMode::Coast);
		m_backRightMotor->SetNeutralMode(NeutralMode::Coast);
	}
}

bool RegularChassis::CanStrafe() const {
	return false;
}

void RegularChassis::SetTalonMode(DragonTalon::TALON_CONTROL_MODE mode) {
//	m_frontLeftMotor->SetControlMode(mode);
//	m_frontRightMotor->SetControlMode(mode);
	m_backLeftMotor->SetControlMode(mode);
	m_backRightMotor->SetControlMode(mode);
}

void RegularChassis::SetDriveMagnitudes(double xPower, double yPower,
		double rotationPower) {
	double leftPower = yPower + rotationPower;
	double rightPower = yPower - rotationPower;

	//Limit max output to -1 to 1.
	double maxValue = 0;
	if (std::abs(leftPower) > maxValue)
		maxValue = std::abs(leftPower);
	if (std::abs(rightPower) > maxValue)
		maxValue = std::abs(rightPower);
	//Scale down all values if max > 1.0
	if (maxValue > 1.0) {
		leftPower /= maxValue;
		rightPower /= maxValue;
	}

	//TODO: change back motors to slave motors
	//Apply motor powers to CANTalons
//	m_frontLeftMotor->Set(leftPower);
	m_backLeftMotor->Set(leftPower);
//	m_frontRightMotor->Set(rightPower);
	m_backRightMotor->Set(rightPower);

	frc::SmartDashboard::PutNumber("left motor set value drive: ", leftPower);
	frc::SmartDashboard::PutNumber("right motor set value drive: ", rightPower);
}

void RegularChassis::SetLeftRightMagnitudes(double leftPower, double rightPower) {
//	m_frontLeftMotor->Set(leftPower);
	m_backLeftMotor->Set(leftPower);
//	m_frontRightMotor->Set(rightPower);
	m_backRightMotor->Set(rightPower);

	frc::SmartDashboard::PutNumber("left motor set value mag: ", leftPower);
	frc::SmartDashboard::PutNumber("right motor set value mag: ", rightPower);
}

void RegularChassis::UpdateChassis() {
	double deltaDistance = GetDistance() - m_pDistance;
	m_pDistance = GetDistance();

	//update location based on encoder and heading data
	double xComponent = std::cos(
			DragonMath::DegreesToRadians(
					DragonMath::HeadingToStandardAngle(GetHeading())));
	double yComponent = std::sin(
			DragonMath::DegreesToRadians(
					DragonMath::HeadingToStandardAngle(GetHeading())));

	//Add the new displacement vector to the robot location
	m_location.x += xComponent * deltaDistance;
	m_location.y += yComponent * deltaDistance;
}

void RegularChassis::PrintDebug() {
	frc::SmartDashboard::PutNumber("back left vel", m_backLeftMotor->GetRPM());
	frc::SmartDashboard::PutNumber("back right vel",
			m_backRightMotor->GetRPM());

	frc::SmartDashboard::PutNumber("back left r",
			m_backLeftMotor->GetRotationCount());
	frc::SmartDashboard::PutNumber("back right r",
			m_backRightMotor->GetRotationCount());

	frc::SmartDashboard::PutNumber("robot heading", GetHeading());

	frc::SmartDashboard::PutNumber("robot X location: ", m_location.x);
	frc::SmartDashboard::PutNumber("robot Y location: ", m_location.y);

//	frc::SmartDashboard::PutNumber("ultrasonic distance: ", m_ultra->GetRangeInches());
//	printf("ultrasonic in inches %g", m_ultra->GetRangeInches());
	frc::SmartDashboard::PutNumber("robot distance: ", GetDistance());
}

void RegularChassis::ResetChassis()
{
	m_location.x = 0;
	m_location.y = 0;
	if ( m_pigeon != nullptr )
	{

	    //  m_pigeon->SetFusedHeading(0, 1000);
	    //  m_pigeon->SetAccumZAngle(0, 100);
	    m_resetHeading = m_pigeon->GetFusedHeading();
	    //  m_pigeon->SetYaw(0, 1000);
	}
	printf("Reset chassis\n");
}

double RegularChassis::GetLeftVelocity() const {
	return m_backLeftMotor->GetRPM() / velocityToRPM;
}

double RegularChassis::GetRightVelocity() const {
	return m_backRightMotor->GetRPM() / velocityToRPM;
}

void RegularChassis::SetVelocityParams(float kP, float kI, float kD, float kF,
		float leftSpeed, float rightSpeed) {
	//Set all talon's closed loop parameters
//	m_frontLeftMotor->SetClosedLoopParams(0, kP, kI, kD, kF, 0 );
	m_backLeftMotor->SetClosedLoopParams(0, kP, kI, kD, kF, 0 );
//	m_frontRightMotor->SetClosedLoopParams(0, kP, kI, kD, kF, 0 );
	m_backRightMotor->SetClosedLoopParams(0, kP, kI, kD, kF, 0 );
	//Run motors
	leftSpeed *= velocityToRPM;
	rightSpeed *= velocityToRPM;
	SetLeftRightMagnitudes(leftSpeed, rightSpeed);
}

void RegularChassis::SetPIDParams(float kP, float kI, float kD, float kF) {
	m_backLeftMotor->SetClosedLoopParams(0, kP, kI, kD, kF, 0);
	m_backRightMotor->SetClosedLoopParams(0, kP, kI, kD, kF, 0);
}

double RegularChassis::GetBestOfTwo(double x1, double x2) const {
	return std::abs(x1) > std::abs(x2) ? x1 : x2;
}

double RegularChassis::GetTargetHeading() const {
	return m_targetHeading;
}

void RegularChassis::EnableCurrentLimiting(bool enabled) {
	m_backLeftMotor->EnableCurrentLimit(enabled);
	m_backRightMotor->EnableCurrentLimit(enabled);
	m_frontLeftMotor->EnableCurrentLimit(enabled);
	m_frontRightMotor->EnableCurrentLimit(enabled);

	if (enabled) {
		int peakTime = 5;   //100
		int sustainAmps = 30; //40
		int peakAmps = 40; //75
		m_backLeftMotor->ConfigPeakCurrentDuration(peakTime, 0);
		m_backLeftMotor->ConfigContinuousCurrentLimit(sustainAmps, 0);
		m_backLeftMotor->ConfigPeakCurrentLimit(peakAmps, 0);

		m_backRightMotor->ConfigPeakCurrentDuration(peakTime, 0);
		m_backRightMotor->ConfigContinuousCurrentLimit(sustainAmps, 0);
		m_backRightMotor->ConfigPeakCurrentLimit(peakAmps, 0);

		m_frontLeftMotor->ConfigPeakCurrentDuration(peakTime, 0);
		m_frontLeftMotor->ConfigContinuousCurrentLimit(sustainAmps, 0);
		m_frontLeftMotor->ConfigPeakCurrentLimit(peakAmps, 0);

		m_frontRightMotor->ConfigPeakCurrentDuration(peakTime, 0);
		m_frontRightMotor->ConfigContinuousCurrentLimit(sustainAmps, 0);
		m_frontRightMotor->ConfigPeakCurrentLimit(peakAmps, 0);
	}
}

void RegularChassis::SetTargetHeading(double heading) {
	m_targetHeading = heading;
}

void RegularChassis::ResetGyro()
{
	m_pigeon->EnterCalibrationMode(ctre::phoenix::sensors::PigeonIMU::CalibrationMode::BootTareGyroAccel, 4000);
}
