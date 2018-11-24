/*
 * LightRingController.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Austin
 */

#include <subsys/vision/LightRingController.h>

LightRingController::LightRingController() :
	m_redChannel ( new frc::PWM(0) ),
	m_greenChannel ( new frc::PWM(1) ),
	m_blueChannel ( new frc::PWM(2) )
{
}

void LightRingController::setOnOff( int type, bool on )
{
	switch( type )
	{
	case LightRingController::RGB:
	if ( on )
	{
		m_redChannel->SetRaw( 50000 );
		m_greenChannel->SetRaw( 50000 );
		m_blueChannel->SetRaw( 50000 );
	}
	else
	{
		m_redChannel->SetRaw( 0 );
		m_greenChannel->SetRaw( 0 );
		m_blueChannel->SetRaw( 0 );
	}
	break;
	case LightRingController::STATIC: // TODO: Need to add spike controller
		break;
	}
}
