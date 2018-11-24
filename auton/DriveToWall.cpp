/*
 * DriveToWall.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: jonah
 */

//Includes
#include <cmath>
#include <iostream>

//Team302 includes
#include <auton/DriveToWall.h>
#include <factories/ChassisFactory.h>
#include <interfaces/IChassis.h>

DriveToWall::DriveToWall() :
	SuperDrive(),
	m_lift(new LiftElevator()),
	m_grabCube(new GrabCube()),
	m_minimumTime(0),
	m_timeRemaining(0),
	m_underSpeedCounts(0)
{
}

void DriveToWall::Init(PrimitiveParams* params) {
	SuperDrive::Init(params);
	m_timeRemaining = params->GetTime();
	m_underSpeedCounts = 0;
	m_minimumTime = 0.3;
	m_lift->Init(params);
	m_grabCube->Init(params);
}

void DriveToWall::Run() {
	if (m_minimumTime <= 0) {
		if (std::abs(ChassisFactory::GetIChassis()->GetVelocity()) < SPEED_THRESHOLD) {
			m_underSpeedCounts++;
		}
	}
	m_lift->Run();
	m_grabCube->Run();

	m_minimumTime -= IPrimitive::LOOP_LENGTH;
	m_timeRemaining -= IPrimitive::LOOP_LENGTH;
}

bool DriveToWall::IsDone() {
	return (m_underSpeedCounts >= UNDER_SPEED_COUNT_THRESHOLD) && m_timeRemaining <= 0;
}

