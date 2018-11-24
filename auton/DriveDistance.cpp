/*
 * DriveDistance.cpp
 *
 *  Created on: Jan 18, 2018
 *      Author: jonah
 */

//Includes
#include <cmath>
#include <SmartDashboard/SmartDashboard.h>

//Team302 includes
#include <auton/DriveDistance.h>
#include <factories/ChassisFactory.h>
#include <interfaces/IChassis.h>

DriveDistance::DriveDistance() :
	SuperDrive(),
	m_params(nullptr),
	m_lift(new LiftElevator()),
	m_grabCube(new GrabCube()),
	m_targetDistance(0),
	m_initialDistance(0),
	m_timeRemaining(0),
	m_minSpeedCountTime(0), //will be changed in init
	m_underSpeedCounts(0),
	m_startHeading(0),
	m_endHeading(0),
	m_minSpeed(0),
	m_arcing(false)
{
}

void DriveDistance::Init(PrimitiveParams* params) {
	SuperDrive::Init(params);
	m_arcing = std::abs(params->GetHeading()) > 0.1;
	m_startHeading = ChassisFactory::GetIChassis()->GetTargetHeading();
	m_endHeading = m_startHeading + params->GetHeading();

	m_minSpeedCountTime = MIN_SPEED_COUNT_TIME;
	m_underSpeedCounts = 0;
	m_params = params;
	//Get parameters from params
	m_targetDistance = params->GetDistance();
	m_initialDistance = ChassisFactory::GetIChassis()->GetDistance();
//	m_timeRemaining = (params->GetDistance() / params->GetDriveSpeed()) * TIMEOUT_MULTIPIER; //TODO: physically test this this
	m_lift->Init(params);
	m_grabCube->Init(params);
	frc::SmartDashboard::PutNumber("initial angle", m_startHeading);
	frc::SmartDashboard::PutNumber("final angle", m_endHeading);
	frc::SmartDashboard::PutNumber("THIS SHOULD BE 0 DURNING SWITCH init", m_params->GetHeading());
}

void DriveDistance::Run() {
	SuperDrive::Run();

	if (m_arcing) {
		//Calculate progress from 0 to 1
		float progress = std::abs(ChassisFactory::GetIChassis()->GetDistance() - m_initialDistance);
		frc::SmartDashboard::PutNumber("progress out of 226", progress);
		progress /= std::abs(m_targetDistance); //progress = progress / targetDistance
		frc::SmartDashboard::PutNumber("dd progress", progress);

		float newTargetHeading = 0;
		//Linear interpolation between start heading and end heading based on progress
		newTargetHeading += (1.0 - progress) * m_startHeading;// newTargetheading = newTargetHeading + (1.0 - progress) * m_startHeading
		newTargetHeading += (progress) * m_endHeading;
		frc::SmartDashboard::PutNumber("new target heading", newTargetHeading);
		ChassisFactory::GetIChassis()->SetTargetHeading(newTargetHeading);
	}

//	frc::SmartDashboard::PutBoolean("arcing", m_arcing);
//	frc::SmartDashboard::PutNumber("THIS SHOULD BE 0 DURNING SWITCH", m_params->GetHeading());

	CalculateSlowDownDistance();
	m_lift->Run();
	m_grabCube->Run();

	if (m_minSpeedCountTime <= 0) {
		if (std::abs(ChassisFactory::GetIChassis()->GetVelocity()) < SPEED_THRESHOLD) {
			m_underSpeedCounts++;
		}
	}
	m_minSpeedCountTime -= IPrimitive::LOOP_LENGTH;
}

bool DriveDistance::IsDone() {
	float progress = ChassisFactory::GetIChassis()->GetDistance() - m_initialDistance;
	bool reachedTarget = std::abs(progress) > std::abs(m_targetDistance);
//	printf("drive distance current dist: %g \n", progress);
	m_timeRemaining -= IPrimitive::LOOP_LENGTH;

	bool notMoving = m_underSpeedCounts >= UNDER_SPEED_COUNT_THRESHOLD;
	bool done = reachedTarget || notMoving;
	if (done) {
		ChassisFactory::GetIChassis()->SetTargetHeading(m_endHeading);
	}
	return done;
}

void DriveDistance::CalculateSlowDownDistance() {
//	if (SuperDrive::ReachedTargetSpeed()) {	//If we reached the targetSpeed, we can calculate the slow down time
//		float slowDownTime = SuperDrive::GetAccelDecelTime();
//		float currentDistance = std::abs(ChassisFactory::GetIChassis()->GetDistance() - m_initialDistance);
//		float distanceRemaining = std::abs(m_targetDistance - currentDistance);
//		float timeRemaining = std::abs(distanceRemaining / m_params->GetDriveSpeed());
//
//		if (timeRemaining <= slowDownTime) {
//			SuperDrive::SlowDown();
//		}
//	}

	float currentVel = ChassisFactory::GetIChassis()->GetVelocity();
//	float decelTime = currentVel - m_params->GetDriveSpeed();
	float decelTime = currentVel / SuperDrive::INCHES_PER_SECOND_SECOND;
//	float decelDist = std::abs(((currentVel + endVel) / 2.0) * accelTime);
//	float decelDist = std::abs((currentVel / 2.0) * decelTime);
	float decelDist = std::abs(((currentVel - m_minSpeed)) * decelTime * DECEL_TIME_MULTIPLIER);
	float currentDistance = std::abs(ChassisFactory::GetIChassis()->GetDistance() - m_initialDistance);
	float distanceRemaining = std::abs(m_targetDistance - currentDistance);

	frc::SmartDashboard::PutNumber("Distance remaining: ", distanceRemaining);
	frc::SmartDashboard::PutNumber("Decel distance: ", decelDist);
	frc::SmartDashboard::PutNumber("Slowing down (1 = true): ", distanceRemaining <= decelDist ? 1 : 0);

	if (distanceRemaining <= decelDist)
	{
		frc::SmartDashboard::PutNumber("distance remaining in drive", distanceRemaining);
		SuperDrive::SlowDown();
	}
}

void DriveDistance::SetDistance
(
    double distance
)
{
    m_targetDistance = distance;
}

