/*
 * SECTOR IS NOT CLEAR, NOT CLEAR!
 * TrueColorsNew.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: casti
 */

#include <CANLight.h>
#include <driverstation.h>
#include <subsys/components/TrueColors.h>

using namespace frc;
using namespace mindsensors;

	TrueColors::TrueColors( int canID ) : m_lights( new CANLight( canID ) )
	{
	}

	TrueColors::~TrueColors()
	{
	    delete m_lights;
	}

	void TrueColors::SetLightMode(TrueColors::LightModes mode)
	{
		DriverStation* ds = &DriverStation::GetInstance();
		switch(mode)
		{
            case CUBE_TARGET_ACQUIRED:
//                m_lights->WriteRegister( 0, 1.0, 255, 255, 0 );
//                m_lights->WriteRegister( 1, 0.5, 0, 0, 0 );
            	m_lights->ShowRGB(255, 255, 0);
//                m_lights->Cycle( 0, 1 );
                break;

            case CLIMBING_SCALE:
                m_lights->WriteRegister( 0, 0.5, 0, 255, 0 );
                m_lights->WriteRegister( 1, 0.5, 255, 255, 255 );
                m_lights->Cycle( 0, 1 );
                break;

            case NORMAL_MODE:
                // watch case for framelights (actually it should just be lights)
                 if(ds->GetAlliance() == DriverStation::Alliance::kRed)
                 {
                     m_lights->ShowRGB( 255, 0, 0 );
                 }
                 else if( ds->GetAlliance() == DriverStation::Alliance::kBlue )
                 {
                     m_lights->ShowRGB( 0, 0, 255 );
                 }
                 else if( ds->GetAlliance() == DriverStation::Alliance::kInvalid )
                 {
                     m_lights->ShowRGB( 0, 255, 0 );
                 }
                 break;

            case TRANSITION_TO_TELEOP:
//                m_lights->WriteRegister( 0, 1.0, 68, 52, 4 );
//                m_lights->WriteRegister( 1, 1.0, 0, 124, 8 );
            	m_lights->WriteRegister( 0, 1.0, 0, 255, 0 );
            	m_lights->WriteRegister( 1, 1.0, 255, 255, 255 );
                m_lights->Cycle( 0, 1 );
                break;
            case HUMAN_PLAYER_SIGNAL:
            	m_lights->ShowRGB( 0, 255, 0);
            	break;

            case DISABLED_MODE:
            	m_lights->WriteRegister(0, 1, 0, 180, 0);
            	m_lights->WriteRegister(1, 1, 180, 180, 120);
            	m_lights->Cycle(0, 1);
            	break;

            default:
            	int maxColor = 50;
                m_lights->WriteRegister( 0, 0.5, maxColor,   0,   0 );
                m_lights->WriteRegister( 1, 0.5, maxColor, maxColor/2,   0 );
                m_lights->WriteRegister( 2, 0.5, maxColor, maxColor,   0 );
                m_lights->WriteRegister( 3, 0.5,   0, maxColor,   0 );
                m_lights->WriteRegister( 4, 0.5,   0,   0, maxColor/2 );
                m_lights->WriteRegister( 5, 0.5,  maxColor/3,   0, maxColor );
                m_lights->WriteRegister( 6, 0.5, maxColor,   0, maxColor );
                m_lights->Cycle( 0, 6 );
                break;
        }
	}




