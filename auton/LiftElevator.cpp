/*
 * PlaceCube.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Austin's mom
 */

#include <auton/GrabCube.h>
#include <auton/LiftElevator.h>

LiftElevator::LiftElevator() :
	m_lift(nullptr),
	m_params(nullptr),
	m_deliverHeight( Lift::KEEP_SAME ),
	m_grabberInit(false)
{
	MechanismFactory* factory = MechanismFactory::GetMechanismFactory();
	if ( factory != nullptr )
	{
		m_lift = dynamic_cast<Lift*>( factory->GetIMechanism( IMechanism::LIFT ) );
	}
}

void LiftElevator::Init( PrimitiveParams* params )
{
	if ( m_lift == nullptr )
	{
		printf("No lift created \n");
	}
	else
	{
		m_grabberInit = false;
		// Get params
		m_deliverHeight = params->GetDeliverHeight();
		m_params = params;

		m_lift->MoveElevatorPreset( m_deliverHeight ); // pass -1 for no movement
	}
}

void LiftElevator::Run()
{
	m_lift->MoveElevatorPreset( m_deliverHeight ); // pass -1 for no movement
}

bool LiftElevator::IsDone()
{
	return m_lift->AtTarget();
}
