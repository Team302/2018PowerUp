/*
 * ClimbHandler.cpp
 */

#include <teleop/controllers/TeleopControl.h>
#include <teleop/controlMechanisms/ClimbHandler.h>

ClimbHandler::ClimbHandler() : m_controller( TeleopControl::GetInstance() ),
							   m_climber( nullptr ),
							   m_sideHanger( nullptr ),
							   m_winchPrevRun( false ),
							   m_tridentUnlocked( false ),
							   m_safetyPrevious( false )
{
	MechanismFactory* factory = MechanismFactory::GetMechanismFactory();
	if ( factory != nullptr )
	{
		m_climber = dynamic_cast<Climber*>( factory->GetIMechanism( IMechanism::CLIMBER ) );
		m_sideHanger = dynamic_cast<SideHanger*>( factory->GetIMechanism( IMechanism::SIDE_HANGER ) );
	}

	if ( m_controller == nullptr )
	{
		printf( "ClimbHandler has no controller \n" );
	}

	if ( m_climber == nullptr )
	{
		printf( "ClimbHandler has no climb mechanism \n" );
	}

	if ( m_sideHanger == nullptr )
	{
		printf( "ClimbHandler has no side hanger mechanism \n" );
	}

}

ClimbHandler::~ClimbHandler()
{
}


//-----------------------------------------------------------------------------------
// Method:          Periodic
// Description:     Run the mechanism
// Returns:         void
//-----------------------------------------------------------------------------------
void ClimbHandler::Periodic()
{
	if ( m_controller != nullptr && m_climber != nullptr )
	{
		// Control Winch
		bool runWinch = m_controller->IsButtonPressed( TeleopControl::RETRACT_WINCH );
		bool reverseWinch = m_controller->IsButtonPressed( TeleopControl::UNRETRACT_WINCH );
		bool holdWinch = m_controller->IsButtonPressed( TeleopControl::HOLD_ROBOT_CLIMB );
		bool toggleSafetySwitch = m_controller->IsButtonPressed( TeleopControl::TOGGLE_SAFTEY_SWITCH );

		if (toggleSafetySwitch && !m_safetyPrevious)
		{
			m_tridentUnlocked = !m_tridentUnlocked;
		}
		m_safetyPrevious = toggleSafetySwitch;

		if ( holdWinch )
		{
			m_climber->HoldWinch();
		}
		else if ( runWinch )
		{
			m_climber->RunWinch();
		}
		else if (!reverseWinch)
		{
		    m_climber->StopWinch();
		}
		else
		{
			m_climber->ReverseWinch();
		}
//
//
//		// Control the Side Hanging Bar
////		bool rotateCW = m_controller->IsButtonPressed( TeleopControl::ROTATE_SIDE_CLIMB_BAR_CW );
////		bool rotateCCW = m_controller->IsButtonPressed( TeleopControl::ROTATE_SIDE_CLIMB_BAR_CCW );
//		float rotateCW = m_controller->IsButtonPressed( TeleopControl::ROTATE_SIDE_CLIMB_BAR_CW );
//		float rotateCCW = m_controller->IsButtonPressed( TeleopControl::ROTATE_SIDE_CLIMB_BAR_CCW );
//		if (m_tridentUnlocked)
//		{
////			if ( rotateCW )
////			{
////			    m_sideHanger->RaiseBar( SideHanger::CLOCKWISE );
////			}
////			else if ( rotateCCW )
////			{
////	            m_sideHanger->RaiseBar( SideHanger::COUNTER_CLOCKWISE );
////			}
////			else
////			{
////			    m_sideHanger->RaiseBar( SideHanger::STOP );
////			}
//			float speed = rotateCW - rotateCCW;
//			speed *= 0.3;
//			m_sideHanger->MoveBar(speed);
//		}
//		else
//		{
////		    m_sideHanger->RaiseBar( SideHanger::STOP );
//			m_sideHanger->MoveBar(0);
//		}
//
//
//        bool releaseTrident = m_controller->IsButtonPressed( TeleopControl::RELEASE_SIDE_HANGER );
//        if ( releaseTrident )
//        {
//            m_sideHanger->ReleaseTrident();
//        }
//
//        bool retractLatch = m_controller->IsButtonPressed( TeleopControl::RETRACT_CLIMB_LATCH );
//        bool extendLatch = m_controller->IsButtonPressed( TeleopControl::EXTEND_CLIMB_LATCH );
//        if ( retractLatch )
//        {
//            m_sideHanger->LatchBar( !retractLatch );
//        }
//        else if ( extendLatch )
//        {
//            m_sideHanger->LatchBar( extendLatch );
//        }
	}

}


