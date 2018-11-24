/*
 * CubeHandler.cpp
 */

#include <factories/CompressorFactory.h>
#include <factories/CubeHandlerFactory.h>
#include <factories/MechanismFactory.h>
#include <factories/LidarFactory.h>
#include <interfaces/ICubeHandler.h>
#include <interfaces/IMechanism.h>
#include <teleop/controllers/TeleopControl.h>
#include <teleop/controlMechanisms/CubeHandler.h>

#include <subsys/mechanisms/ActiveGrabber.h>
#include <subsys/mechanisms/Grabber.h>
#include <subsys/mechanisms/Lift.h>

#include <teleop/controlMechanisms/CubeToFloor.h>
#include <teleop/controlMechanisms/CubeToSwitch.h>
#include <teleop/controlMechanisms/CubeToScale.h>
#include <teleop/controlMechanisms/CubeHoldPos.h>
#include <teleop/controlMechanisms/CubeManualControl.h>

#include <SmartDashboard/SmartDashboard.h>
#include <cmath>

CubeHandler::CubeHandler() : m_controller( TeleopControl::GetInstance() ),
							 m_grabber( nullptr ),
							 m_activeGrabber( nullptr ),
							 m_lift( nullptr ),
							 m_currentState( ICubeHandler::MANUAL_CONTROL ),
							 m_dbPassed ( false ),
							 m_safetyToggle( false ),
							 m_prevBackButton( false ),
							 m_fourBarState( true )
{
//	printf("CubeHandler constructed\n");
	MechanismFactory* factory = MechanismFactory::GetMechanismFactory();
	if ( factory != nullptr )
	{
		m_grabber = dynamic_cast<Grabber*>( factory->GetIMechanism( IMechanism::GRABBER ) );
		m_activeGrabber = dynamic_cast<ActiveGrabber*>( factory->GetIMechanism( IMechanism::ACTIVE_GRABBER ) );
        m_lift = dynamic_cast<Lift*>( factory->GetIMechanism( IMechanism::LIFT ) );
	}

	if ( m_controller == nullptr )
	{
		printf( "CubeHandler has no controller \n" );
	}

    if ( m_grabber == nullptr && m_activeGrabber == nullptr )
    {
        printf( "CubeHandler has no grabber mechanism \n" );
    }

    if ( m_lift == nullptr )
    {
        printf( "CubeHandler has no lift mechanism \n" );
    }
}


//-----------------------------------------------------------------------------------
// Method:          Periodic
// Description:     Run the mechanism
// Returns:         void
//-----------------------------------------------------------------------------------
void CubeHandler::Periodic()
{
    if ( m_controller != nullptr && m_activeGrabber != nullptr )
	{
		// Control Lift
	    bool toggleSafetySwitch 	= m_controller->IsButtonPressed( TeleopControl::TOGGLE_SAFTEY_SWITCH );
        bool raise4Bar    			= m_controller->IsButtonPressed( TeleopControl::RAISE_4BAR );
        bool lower4Bar              = m_controller->IsButtonPressed( TeleopControl::LOWER_4BAR );
        float elevMove 				= m_controller->GetAxisValue( TeleopControl::MANUAL_ELEVATOR_CONTROL );
        float manualFourbarSpeed    = m_controller->GetAxisValue( TeleopControl::MANUAL_MOVE_4BAR_MOTOR );
        // Control Grabber
        bool closeGrabber 			= m_controller->IsButtonPressed( TeleopControl::GRAB_CUBE );
        bool spinGrabber 			= m_controller->IsButtonPressed( TeleopControl::SPIN_CUBE );
        float intakeSpeed 			= m_controller->GetAxisValue( TeleopControl::INTAKE_CUBE );
        bool wiggleCube				= m_controller->IsButtonPressed( TeleopControl::WIGGLE_CUBE );




        bool winchActive			= m_controller->IsButtonPressed( TeleopControl::RETRACT_WINCH );

        bool haveCube				= m_activeGrabber->GetCubePresent();
        SmartDashboard::PutBoolean("CUBE PRESENT", haveCube);

        // TODO:  need to test
        // if pressure is low, don't open the grabber
        CompressorFactory* factory = CompressorFactory::GetFactory();
        if ( factory != nullptr )
        {
        	DragonAnalogInput* gauge = factory->GetPressureGauge();
        	if ( gauge != nullptr )
        	{
        		float press = gauge->GetInterpolatedValue();
        		if ( press < 70.0 ) //60 //81
        		{
        			closeGrabber = false;
        		}
        	}
        }

    	SmartDashboard::PutBoolean("Elevator Manual", m_safetyToggle);

        if ( toggleSafetySwitch && !m_prevBackButton )
        {
        	m_safetyToggle = !m_safetyToggle;

        }

        if ( m_activeGrabber != nullptr )
        {
        	if (wiggleCube)
        	{
        		m_activeGrabber->WiggleCube();
        	}
        	else
        	{
        		m_activeGrabber->SpinWheels( intakeSpeed );
        	}

            m_activeGrabber->CloseActiveGrabber( closeGrabber );
        }
        else if ( m_grabber != nullptr )
        {
            m_grabber->SpinGrabber( spinGrabber );
            m_grabber->CloseGrabber( closeGrabber );
        }

        if (raise4Bar)
        {
        	m_fourBarState = true;
        }
        if (lower4Bar)
        {
        	m_fourBarState = false;
        }

        float fourbarSpeed = (raise4Bar ? 0.80 : 0) + (lower4Bar ? -0.60 : 0);
//        frc::SmartDashboard::PutBoolean("DPAD UP", raise4Bar);
//        frc::SmartDashboard::PutBoolean("DPAD DOWN", lower4Bar);
        m_lift->SetFourbarPower( fourbarSpeed );
        if (std::abs(manualFourbarSpeed) > 0.2)
        {
        	m_lift->SetFourbarPower( manualFourbarSpeed );
        }
        else
        {
//        	m_lift->MoveFourbar( m_fourBarState );
        }

        //If the winch is active, we should always be in climb mode
        //else, turn it off when we start using the elevator again (when that joystick is outside of the dead band)
        if (winchActive)
        {
        	m_lift->SetClimbMode(true);
        }
        else
        {
        	if (std::abs(elevMove) > DEAD_BAND)
        	{
        		m_lift->SetClimbMode(false);
        	}
        }

        m_lift->MoveElevatorMotor( elevMove > 0 ? std::pow(elevMove, 3) : std::pow(elevMove, 3), m_safetyToggle );

        m_prevBackButton = toggleSafetySwitch;
	}
}

void CubeHandler::ResetHeight() {
	m_lift->MoveElevatorPreset(Lift::FLOOR);
}


