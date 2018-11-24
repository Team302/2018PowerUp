/*
 * Gamepad.cpp
 *
 *  Created on: Jan 31, 2018
 *      Author: Chris
 *      TODO: WE must check if this actually works. And document this.
 */

#include <SmartDashboard/SmartDashboard.h>

#include <stdio.h>

#include <cmath>

#include <GenericHID.h>

#include <interfaces/IDragonController.h>

////#include <utils/LimitValue.h>

#include <joystick.h>
#include <teleop/controllers/DragonGamepad.h>

using namespace frc;

/*Constructor:
 *
 * constructs the methods for this file.
*/
DragonGamepad::DragonGamepad( int port ) : IDragonController(),
	m_gamepad( new Joystick( port ) ),
	m_count(),
	m_axisScale(),
	m_axisInversionFactor(),
	m_axisProfile()
//	m_joy()
//	value()
	{
	// TODO Auto-generated constructor stub



		if ( MAX_GAMEPAD_AXIS > m_maxAxis ) //checks for errors
		{
			SmartDashboard::PutString( "Axis Error", " OOF! gamepad.h has stopped working. there are more GAMEPAD axis slots than array slots \n " );
		}

		for ( auto inx=0; inx<m_maxAxis; ++inx )
		{
			m_axisScale[inx] = STD_RANGE_SCALING;
			m_axisInversionFactor[inx] = DONT_INVERT_AXIS;
			m_axisProfile[inx] = AXIS_LINEAR;
		}
	}

float DragonGamepad::GetAxisValue
(
		AXIS_IDENTIFIER 	axis
) const
{
	double output = 0.0;
	if ( axis < MAX_GAMEPAD_AXIS )
	{
		switch ( axis )//switch method to find out the axes for each gamepad buttons that use axis.
		{
		case GAMEPAD_AXIS_16:
			output = m_gamepad->GetY( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_AXIS_17:
			output = m_gamepad->GetY( GenericHID::kRightHand ) * m_axisInversionFactor[ axis ];
			break;

		// jw - changed 2 to axis
		case GAMEPAD_DIAL_22: //Dial has six settings, 22-27.
			output = m_gamepad->GetY( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_23:
			output = m_gamepad->GetY( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_24:
			output = m_gamepad->GetY( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_25:
			output = m_gamepad->GetY( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_26:
			output = m_gamepad->GetY( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_27:
			output = m_gamepad->GetY( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		default:
			break;

		}
		if (std::abs(output) < DEAD_BAND_THRESH)
		{
			output = 0.0;
		}
		else if (std::abs(output) > DEAD_BAND_THRESH)
		{
			if ( m_axisProfile[axis] == AXIS_CUBIC )
			{
				output = pow( output, 3.0 );
			}
			output = output * m_axisScale[axis];
		}
	}
	return output;
}

void DragonGamepad::FindButtonAxis(int m_count)//This finds what axis each button uses.
{
//  if ( m_count == 0 )
//  {
//	for ( int inx=0; inx<7; ++inx )
//	{
//		printf( "Axis [ %d ] = %g \n", inx, m_gamepad->GetRawAxis(inx) );
//	}
//	for ( int inx=0; inx<11; ++inx )
//	{
//		printf( "Button [ %d ] = %s \n", inx, m_gamepad->GetRawButton(inx) ? "true" : "false" );
//	}
//  }
//  m_count++;
//
//  if ( m_count > 100 )
//  {
//	  m_count = 0;
//  }

}
bool DragonGamepad::IsButtonPressed //Finds out what button is pressed. If the button uses axis, it will have a lowerband and upperband,
(
        BUTTON_IDENTIFIER    button         // <I> - button to check
) const
{

	bool pressed = false;
	double value = 0.0;

	switch(button)
	{
	case GAMEPAD_BUTTON_1:
		value = m_gamepad->GetRawAxis( button_1_axis );
		if ( value > button_1_lowerband && value < button_1_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean(" Gamepad 1 pressed", pressed);
		break;
	case GAMEPAD_BUTTON_2:
		value = m_gamepad->GetRawAxis( button_2_axis );
		if ( value > button_2_lowerband && value < button_2_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean(" Gamepad 2 pressed", pressed);
		break;
	case GAMEPAD_BUTTON_3:
		value = m_gamepad->GetRawAxis( button_3_axis );
		if ( value > button_3_lowerband && value < button_3_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 3 pressed", pressed);
		break;

	case GAMEPAD_BUTTON_4:
		value = m_gamepad->GetRawAxis( button_4_axis );
		if ( value > button_4_lowerband && value < button_4_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 4 pressed", pressed );
		break;
	case GAMEPAD_BUTTON_5:
		value = m_gamepad->GetRawAxis( button_5_axis );
		if (value > button_5_lowerband && value < button_5_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 5 pressed", pressed );
		break;

	case GAMEPAD_BUTTON_6:
		value = m_gamepad->GetRawAxis( button_6_axis );
		if (value > button_6_lowerband && value < button_6_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 6 pressed", pressed );
		break;

	case GAMEPAD_BUTTON_7:
		value = m_gamepad->GetRawAxis( button_7_axis );
		if ( value > button_7_lowerband && value < button_7_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 7 pressed", pressed);
		break;

	case GAMEPAD_BUTTON_8:
		value = m_gamepad->GetRawAxis( button_8_axis );
		if ( value > button_8_lowerband && value < button_8_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 8 pressed", pressed);
		break;

	case GAMEPAD_BUTTON_9:
		value = m_gamepad->GetRawAxis( button_9_axis );
		if ( value > button_9_lowerband && value < button_9_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 9 pressed", pressed);
		break;

	case GAMEPAD_BUTTON_10:
		value = m_gamepad->GetRawAxis( button_10_axis );
		if ( value > button_10_lowerband && value < button_10_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 10 pressed", pressed);
		break;
	case GAMEPAD_BUTTON_11:
		value = m_gamepad->GetRawAxis( button_11_axis );
		if ( value > button_11_lowerband && value < button_11_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 11 pressed", pressed);
		break;

	case GAMEPAD_BUTTON_12:
		value = m_gamepad->GetRawAxis( button_12_axis );
		if ( value > button_12_lowerband && value < button_12_upperband )
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
		frc::SmartDashboard::PutBoolean("Gamepad 12 pressed", pressed);
		break;
		//case GAMEPAD_BUTTON_13.
		//This button doesn't do anything, so it is reserved for later.
		//neither does The Big Red Button.
	case GAMEPAD_SWITCH_18:
		pressed = m_gamepad->GetRawButton( 1 );
		frc::SmartDashboard::PutBoolean("Gamepad 18 switch pressed", pressed);
		break;

	case GAMEPAD_SWITCH_19:
		pressed = m_gamepad->GetRawButton( 2 );
		frc::SmartDashboard::PutBoolean("Gamepad 19 switch pressed", pressed);
		break;

	case GAMEPAD_SWITCH_20:
		pressed = m_gamepad->GetRawButton( 3 );
		frc::SmartDashboard::PutBoolean("Gamepad 20 switch pressed", pressed);
		break;

	case GAMEPAD_SWITCH_21:
		pressed = m_gamepad->GetRawButton( 4 );
		frc::SmartDashboard::PutBoolean("Gamepad 21 switch pressed", pressed);
		break;
	case GAMEPAD_BUTTON_14_UP:
		pressed = m_gamepad->GetRawButton( 7 );
		frc::SmartDashboard::PutBoolean("Gamepad 14 switch pressed up", pressed);
		break;
	case GAMEPAD_BUTTON_14_DOWN:
		pressed = m_gamepad->GetRawButton( 6 );
		frc::SmartDashboard::PutBoolean("Gamepad 14 switch pressed down", pressed);
		break;
	case GAMEPAD_BUTTON_15_UP:
		pressed = m_gamepad->GetRawButton( 9 );
		frc::SmartDashboard::PutBoolean("Gamepad 15 switch pressed up", pressed);
		break;
	case GAMEPAD_BUTTON_15_DOWN:
		pressed = m_gamepad->GetRawButton( 8 );
		frc::SmartDashboard::PutBoolean("Gamepad 15 switch pressed down", pressed);
		break;
	default:
		pressed = false;
		break;
	}
	return pressed;
}
	void DragonGamepad::SetAxisProfile
	(
		AXIS_IDENTIFIER		axis,
		AXIS_SENSITIVITY_CURVE	curve
	)
	{
		if ( axis < MAX_GAMEPAD_AXIS )
		{
			m_axisProfile[ axis ] = curve;
		}
	}

	void DragonGamepad::SetAxisScale
	(
		AXIS_IDENTIFIER			axis,
		float					scaleFactor
	)
	{
		if ( axis < MAX_GAMEPAD_AXIS )
		{
			float axisRange = LimitValue::ForceInRange(scaleFactor, 0.0, 1.0);
			m_axisScale[ axis ] = axisRange;
		}
	}


