/*
 * DoNothing.cpp
 *
 *  Created on: Jan 18, 2018
 *      Author: jonah
 */

#include <auton/DoNothing.h>
#include <auton/PrimitiveParams.h>
#include <interfaces/IPrimitive.h>
#include <factories/ChassisFactory.h>

DoNothing::DoNothing() : m_maxTime(0),
						m_currentTime(0),
						m_chassis(ChassisFactory::GetIChassis()),
						m_lift(new LiftElevator),
						m_grabCube(new GrabCube)
{
}

void DoNothing::Init(PrimitiveParams* params) {
	m_maxTime = params->GetTime();
	m_currentTime = 0.0;
	m_lift->Init(params);
	m_grabCube->Init(params);
}

void DoNothing::Run() {
//    m_chassis->SetDriveMagnitudes(0, 0, 0);
	m_chassis->SetTalonMode(DragonTalon::PERCENT);
    m_chassis->SetLeftRightMagnitudes(0.0, 0.0);
	m_currentTime += LOOP_LENGTH;
	m_lift->Run();
	m_grabCube->Run();

	/*TODO: functionality will be needed in chassis to determine if we are in throttle mode or
	 * velocity mode. this can be done with an enum DRIVE_CONTROL_MODE or something like that
	 * we can either have different motor driving methods for each type and have it automatically switch to the last called type
	 * or we could do it like last year and manually switch the mode whenever we need to use the motors.
	 * as of right now, we aren't doing encoder stuff so i'llll fix this later.
	 */
}

bool DoNothing::IsDone() {
	return m_currentTime >= m_maxTime;
}
