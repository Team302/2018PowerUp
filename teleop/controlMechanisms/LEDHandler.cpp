/*
 * LEDHandler.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: Austin
 */

#include <teleop/controlMechanisms/LEDHandler.h>

LEDHandler::LEDHandler() :
						m_ran(false),
						m_leds(nullptr),
						m_activeGrabber(nullptr),
						m_grabber(nullptr),
						m_lift(nullptr),
						m_climber(nullptr),
						m_controller(TeleopControl::GetInstance()),
						m_downLidar(nullptr)
{
		MechanismFactory* mechanism_factory = MechanismFactory::GetMechanismFactory();
		LEDFactory* led_factory = LEDFactory::GetFactory();

		if (led_factory != nullptr)
		{
//			m_leds = dynamic_cast<TrueColors*>( led_factory->GetLEDs() );
			m_leds = LEDFactory::GetFactory()->GetLEDs();
		}
		else
		{
			printf("YO THATS NULL (that led factory is null)\n");
		}

		if ( mechanism_factory != nullptr )
		{
			m_grabber = dynamic_cast<Grabber*>( mechanism_factory->GetIMechanism( IMechanism::GRABBER ) );
			m_activeGrabber = dynamic_cast<ActiveGrabber*>( mechanism_factory->GetIMechanism( IMechanism::ACTIVE_GRABBER ) );
	        m_lift = dynamic_cast<Lift*>( mechanism_factory->GetIMechanism( IMechanism::LIFT ) );
	        m_climber = dynamic_cast<Climber*>( mechanism_factory->GetIMechanism( IMechanism::CLIMBER ) );
		}
		else
		{
			printf("that mecanism factory is null (in LEDHandler) \n");
		}

		if (m_controller == nullptr)
		{
			printf("LEDHandler has no controller");
		}
		else
		{
			if ( m_grabber == nullptr && m_activeGrabber == nullptr )
	    	{
	        	printf( "LEDHandler has no grabber mechanism \n" );
	    	}

	    	if ( m_lift == nullptr )
	    	{
	        	printf( "LEDHandler has no lift mechanism \n" );
	    	}

	    	if ( m_climber == nullptr )
	    	{
	    		printf( "LEDHandler has no climber mechanism \n");
	    	}
		}

		m_downLidar = LidarFactory::GetLidarFactory()->GetLidar( DragonLidar::DOWNWARD_GRABBER );
}

void LEDHandler::AutonLED()
{
	if ( m_activeGrabber->GetCubePresent() ) // we have a cube
	{
		m_leds->SetLightMode( TrueColors::LightModes::CUBE_TARGET_ACQUIRED );
	}
	else
	{
		m_leds->SetLightMode( TrueColors::LightModes::NORMAL_MODE );
	}
}

void LEDHandler::TeleopLED()
{
    bool humanPlayerSignal 	= m_controller->IsButtonPressed( TeleopControl::HUMAN_PLAYER_SIGNAL );
    bool isClimbing         = m_controller->IsButtonPressed( TeleopControl::RETRACT_WINCH );

	// TODO: Should we have lift heights or some signal for if we are over the scale/switch
	if ( !m_ran )
	{
		m_leds->SetLightMode( TrueColors::LightModes::TRANSITION_TO_TELEOP );
		m_ran = true;
	}
	else if ( humanPlayerSignal )
	{
		m_leds->SetLightMode( TrueColors::LightModes::HUMAN_PLAYER_SIGNAL );
	}
//	else if ( m_lift->GetElevatorRotationCount() > m_lift->heightCounts[0] && m_downLidar->GetDistance() < 36 )
//	{
//		m_leds->SetLightMode( TrueColors::LightModes::HUMAN_PLAYER_SIGNAL );
//	}
	else if ( m_activeGrabber->GetCubePresent() ) // we have a cube
	{
		m_leds->SetLightMode( TrueColors::LightModes::CUBE_TARGET_ACQUIRED );
	}
	else if ( isClimbing ) // we are Climbing
	{
		m_leds->SetLightMode( TrueColors::LightModes::CLIMBING_SCALE );
	}
	else
	{
		m_leds->SetLightMode( TrueColors::LightModes::NORMAL_MODE );
	}
}

void LEDHandler::DisabledLED()
{
	m_leds->SetLightMode( TrueColors::LightModes::DISABLED_MODE );
}

