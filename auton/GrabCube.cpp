/*
 * GrabCube.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: Austin
 */

#include <auton/GrabCube.h>

GrabCube::GrabCube() :
	m_grabber(nullptr),
	m_params(nullptr),
	m_ran(false)
{
	MechanismFactory* factory = MechanismFactory::GetMechanismFactory();
	if ( factory != nullptr)
	{
		m_grabber = dynamic_cast<ActiveGrabber*>( factory->GetIMechanism( IMechanism::ACTIVE_GRABBER ) );
	}
}

void GrabCube::Init(PrimitiveParams* params)
{
	m_params = params;
}

void GrabCube::Run()
{
	if ( m_grabber == nullptr )
	{
		printf("No grabber created \n");
	}
	else
	{
		m_grabber->CloseActiveGrabber(m_params->GetGrab());
		m_grabber->SpinWheels(m_params->GetCubeSpeed());
		m_ran = true;
	}
}

bool GrabCube::IsDone()
{
	return m_ran;
}
