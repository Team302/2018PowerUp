/*
 * CubeManualControl.cpp
 */

#include <factories/MechanismFactory.h>
#include <teleop/controlMechanisms/CubeManualControl.h>

#include <interfaces/ICubeHandler.h>
#include <interfaces/IMechanism.h>
#include <teleop/controllers/TeleopControl.h>
#include <teleop/controlMechanisms/CubeHandler.h>
#include <factories/CubeHandlerFactory.h>

#include <subsys/mechanisms/Grabber.h>
#include <subsys/mechanisms/Lift.h>

CubeManualControl::CubeManualControl() : m_controller( TeleopControl::GetInstance() ),
	                                     m_lift( nullptr )
{
	MechanismFactory* factory = MechanismFactory::GetMechanismFactory();
	if ( factory != nullptr )
	{
		m_lift = dynamic_cast<Lift*>( factory->GetIMechanism( IMechanism::LIFT ) );
	}

	if ( m_controller == nullptr )
	{
		printf( "CubeManualControl has no controller \n" );
	}

	if ( m_lift == nullptr )
	{
		printf( "CubeManualControl has no lift mechanism \n" );
	}
}

//-----------------------------------------------------------------------------------
// Method:          Periodic
// Description:     Run the mechanism
// Returns:         ICubeHandler::CURRENT_CUBEHANDLER_STATE		next state to run
//-----------------------------------------------------------------------------------
ICubeHandler::CURRENT_CUBEHANDLER_STATE CubeManualControl::Periodic()
{
//    printf( "CubeManualControl \n " );
	ICubeHandler::CURRENT_CUBEHANDLER_STATE state = ICubeHandler::MANUAL_CONTROL;
	if ( m_controller != nullptr && m_lift != nullptr )
	{

//		bool moveToSwitchPos = m_controller->IsButtonPressed( TeleopControl::GRABBER_AT_SWITCH_POS );
//		bool moveToScalePos = m_controller->IsButtonPressed( TeleopControl::GRABBER_AT_SCALE_POS );
		bool raise4Bar    = m_controller->IsButtonPressed( TeleopControl::RAISE_4BAR );
//		float elevMove = m_controller->GetAxisValue( TeleopControl::MANUAL_ELEVATOR_CONTROL );

//		printf( " elevMove %g \n ", elevMove );
//		printf( " raise bar %s \n", raise4Bar ? "true" : "false" );
		if ( raise4Bar )
		{
            state = ICubeHandler::MANUAL_CONTROL;
//            m_lift->MoveFourbar( raise4Bar );
            m_lift->SetFourbarState(raise4Bar);
		}

		/*

		bool moveToFloorPos = m_controller->IsButtonPressed( TeleopControl::GRABBER_AT_FLOOR_POS );
		if ( moveToFloorPos )
		{
			state = ICubeHandler::MOVE_TO_FLOOR_POS;
			m_lift->MoveElevatorPreset( Lift::FLOOR );
		}
		else if ( moveToSwitchPos )
		{
			state = ICubeHandler::MOVE_TO_SWITCH_POS;
			m_lift->MoveElevatorPreset( Lift::SWITCH );
		}
		else if ( moveToScalePos )
		{
			state = ICubeHandler::MOVE_TO_SCALE_POS;
			m_lift->MoveElevatorPreset( Lift::SCALE );
		}
		else if ( raise4Bar || std::abs( elevMove ) > 0.2 )
		{
			state = ICubeHandler::MANUAL_CONTROL;
			m_lift->MoveFourbarSolenoid( raise4Bar );
			if ( std::abs( elevMove ) > 0.2 )
			{
				m_lift->MoveElevatorMotor( elevMove );
			}
			else
			{
				m_lift->HoldElevatorPosition();
			}
		}
		else
		{
			state = ICubeHandler::HOLD_POS;
			m_lift->HoldElevatorPosition();
		}
		*/
	}
	return state;
}


