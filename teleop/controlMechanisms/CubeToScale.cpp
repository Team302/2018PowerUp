/*
 * CubeToScale.cpp
 */

#include <factories/MechanismFactory.h>
#include <teleop/controlMechanisms/CubeToScale.h>

#include <interfaces/ICubeHandler.h>
#include <interfaces/IMechanism.h>
#include <teleop/controllers/TeleopControl.h>
#include <teleop/controlMechanisms/CubeHandler.h>
#include <factories/CubeHandlerFactory.h>

#include <subsys/mechanisms/Grabber.h>
#include <subsys/mechanisms/Lift.h>


CubeToScale::CubeToScale() : m_controller( TeleopControl::GetInstance() ),
							 m_lift( nullptr )
{
	MechanismFactory* factory = MechanismFactory::GetMechanismFactory();
	if ( factory != nullptr )
	{
		m_lift = dynamic_cast<Lift*>( factory->GetIMechanism( IMechanism::LIFT ) );
	}

	if ( m_controller == nullptr )
	{
		printf( "CubeToScale has no controller \n" );
	}

	if ( m_lift == nullptr )
	{
		printf( "CubeToScale has no lift mechanism \n" );
	}
}

//-----------------------------------------------------------------------------------
// Method:          Periodic
// Description:     Run the mechanism
// Returns:         void
//-----------------------------------------------------------------------------------
ICubeHandler::CURRENT_CUBEHANDLER_STATE CubeToScale::Periodic()
{
	ICubeHandler::CURRENT_CUBEHANDLER_STATE state = ICubeHandler::MOVE_TO_SCALE_POS;
	if ( m_controller != nullptr && m_lift != nullptr )
	{

		bool moveToSwitchPos = m_controller->IsButtonPressed( TeleopControl::GRABBER_AT_SWITCH_POS );
		bool moveToScalePos = m_controller->IsButtonPressed( TeleopControl::GRABBER_AT_SCALE_POS );
		bool raise4Bar    = m_controller->IsButtonPressed( TeleopControl::RAISE_4BAR );
		float elevMove = m_controller->GetAxisValue( TeleopControl::MANUAL_ELEVATOR_CONTROL );

		bool moveToFloorPos = m_controller->IsButtonPressed( TeleopControl::GRABBER_AT_FLOOR_POS );
		if ( moveToFloorPos )
		{
			state = ICubeHandler::MOVE_TO_FLOOR_POS;
		}
		else if ( moveToSwitchPos )
		{
			state = ICubeHandler::MOVE_TO_SWITCH_POS;
		}
		else if ( moveToScalePos )
		{
			state = ICubeHandler::MOVE_TO_SCALE_POS;
			m_lift->MoveElevatorPreset( Lift::SCALE );
		}
		else if ( raise4Bar )
		{
			state = ICubeHandler::MANUAL_CONTROL;
		}
		else if ( std::abs( elevMove ) > 0.2 )
		{
			state = ICubeHandler::MANUAL_CONTROL;
		}
		else
		{
			state = ICubeHandler::HOLD_POS;
		}
	}
	return state;
}


