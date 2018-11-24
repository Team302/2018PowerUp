/*
 * DragonXBox.cpp
 *
 *========================================================================================================
 *
 * File Description:
 *
 * TODO:: Add documentation about what this class does
 *========================================================================================================*/
#include <stdio.h>

#include <XboxController.h>
#include <GenericHID.h>
#include <interfaces/IDragonController.h>

#include <SmartDashboard/SmartDashboard.h>  	// Smart Dashboard
#include <teleop/controllers/DragonXbox.h>
#include <utils/LimitValue.h>

#include <cmath>        // std:abs

using namespace frc;


//-------------------------------------------------------------------------------------------------
// Method:      <<Constructor>>
// Description: Create a DragonXbox object .
//-------------------------------------------------------------------------------------------------
// MRW look at your data type in DragonXbox.h so the correct type is passed in, m_axisProfile is an array
DragonXbox::DragonXbox
(
	int		port		// <I> - port the controller is connected to
) : IDragonController(),
	m_xbox( new XboxController( port ) ),
    m_axisScale(),
    m_axisInversionFactor(),
	m_axisProfile()
{
    // verify we have enough axis slots and if we don't write a message to the log file
    if ( MAX_XBOX_AXIS > m_maxAxis )
    {
    	SmartDashboard::PutString( "Axis Error", "Houston we have a problem ... there are more XBOX axis than we have array slots \n" );
    }

    // Initialize the attributes for all of the axis to the defaults
    for ( auto inx=0; inx<m_maxAxis; ++inx )
    {
        m_axisScale[inx] = STD_RANGE_SCALING;           // range is -1.0 to 1.0
        m_axisInversionFactor[inx] = DONT_INVERT_AXIS;  // values are whatever is read from the axis
        m_axisProfile[inx] = AXIS_LINEAR;  				// scaling curve is 1.0
    }
	
    // Modify the axis without default values
    // - Y axis are inverted
		m_axisInversionFactor[XBOX_Y_AXIS_LEFT_JOYSTICK] = INVERT_AXIS;
		m_axisInversionFactor[XBOX_Y_AXIS_RIGHT_JOYSTICK] = INVERT_AXIS;
}



//----------------------------------------------------------------------------------
// Method:      GetAxisValue
// Description: This returns the scaled and curve profiled axis value for the specified axis
//
//              NOTE:  the order of operations is important because if deadband is
//              done, last, for instance, the output would lose a lot of the benefit
//              of the scaling curve (power).  For instance, if a value of 0.5 were read
//              from the axis and 0.2 was the deadband, if the curve was cubic, it
//              would calculate a value of 0.125 which would be below the deadband
//              threshold, so it would return 0.0.  On the otherhand, if deadbanding
//              is done on the raw value, 0.125 would be returned.  In fact, in
//              the first scenario, the axis would need to read almost 0.6 before
//              a non-zero value would be returned (at which point 0.2 is returned), so
//              only 0.4 of the range is returning non-zero numbers.  Comparing this
//              to the second case, at 0.2 a value of .008 is calculated and returned.
// Returns:     double output - scaled, deadbanded, and curve profiled output of axis
//----------------------------------------------------------------------------------
float DragonXbox::GetAxisValue
(
    AXIS_IDENTIFIER    axis        // <I> - axis identifier to read
) const
{
    double output = 0.0;    //zero output to start
    if ( axis < MAX_XBOX_AXIS )
    {
        // read the appropriate value from the xbox controller & multiply it by the inversion factor
        switch ( axis )
        {
            case XBOX_X_AXIS_LEFT_JOYSTICK:
                output = m_xbox->GetX( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
                break;
			case XBOX_Y_AXIS_LEFT_JOYSTICK:
                output = m_xbox->GetY( GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
                break;

            case XBOX_X_AXIS_RIGHT_JOYSTICK:
                output = m_xbox->GetX( GenericHID::kRightHand ) * m_axisInversionFactor[ axis ];
                break;
			case XBOX_Y_AXIS_RIGHT_JOYSTICK:
                output = m_xbox->GetY( GenericHID::kRightHand ) * m_axisInversionFactor[ axis ];
                break;

            default:
                break;
        }

		if (std::abs(output) < DEAD_BAND_THRESH)
		{
			output = 0.0;
		}
		else if (std::abs(output) > DEAD_BAND_THRESH )
		{
			if ( m_axisProfile[axis] == AXIS_CUBIC )
			{
				output = pow( output, 3.0 );
			}
			output = output * m_axisScale[axis];
		}
    }
    return output; //returns scaled, profiled, deadbanded joystick output
}

//----------------------------------------------------------------------------------
// Method:      IsButtonPressed
// Description: This returns the scaled and curve profiled axis value for the specified axis
// Parameters:  button - BUTTON_IDENTIFIER enum to select which button to check
// Returns:     bool - true for button pressed
//----------------------------------------------------------------------------------
bool DragonXbox::IsButtonPressed
(
    BUTTON_IDENTIFIER    button         // <I> - button to check
) const
{
    bool pressed = false;
    int povAngle = m_xbox->GetPOV();

    //switch statement to check if button is pressed depending on which button is identified
    switch(button)
    {
        case XBOX_A_BUTTON:
            pressed = m_xbox->GetAButton();
            break;
		case XBOX_B_BUTTON:
            pressed = m_xbox->GetBButton();
            break;
		case XBOX_X_BUTTON:
            pressed = m_xbox->GetXButton();
            break;
		case XBOX_Y_BUTTON:
            pressed = m_xbox->GetYButton();
            break;
		case XBOX_LEFT_BUMPER:
            pressed = m_xbox->GetBumper(GenericHID::kLeftHand);
            break;
		case XBOX_RIGHT_BUMPER:
            pressed = m_xbox->GetBumper(GenericHID::kRightHand);
            break;
		case XBOX_BACK_BUTTON:
            pressed = m_xbox->GetBackButton();
            break;
		case XBOX_START_BUTTON:
            pressed = m_xbox->GetStartButton();
            break;
        case XBOX_PRESS_LEFT_STICK:
            pressed = m_xbox->GetStickButton( GenericHID::kLeftHand );
            break;
		case XBOX_PRESS_RIGHT_STICK:
            pressed = m_xbox->GetStickButton( GenericHID::kRightHand );
            break;
		case XBOX_LEFT_TRIGGER_PRESSED:
            pressed = (m_xbox->GetTriggerAxis( GenericHID::kLeftHand )) > TRIGGER_PRESSED_THRESH; //if trigger value is greater than threshold return true
            break;
		case XBOX_RIGHT_TRIGGER_PRESSED:
            pressed = (m_xbox->GetTriggerAxis( GenericHID::kRightHand )) > TRIGGER_PRESSED_THRESH; //if trigger value is greater than threshold return true
            break;

        case XBOX_POV_0_PRESSED:
            pressed = (povAngle == 0);
            break;

        case XBOX_POV_45_PRESSED:
            pressed = (povAngle == 45);
            break;

        case XBOX_POV_90_PRESSED:
            pressed = (povAngle == 90);
            break;

        case XBOX_POV_135_PRESSED:
            pressed = (povAngle == 135);
            break;

        case XBOX_POV_180_PRESSED:
            pressed = (povAngle == 180);
            break;

        case XBOX_POV_225_PRESSED:
            pressed = (povAngle == 225);
            break;

        case XBOX_POV_270_PRESSED:
            pressed = (povAngle == 270);
            break;

        case XBOX_POV_315_PRESSED:
            pressed = (povAngle == 315);
            break;

        default:
            pressed = false;
            break;
    }

    return pressed; //returns bool for is button pressed
}

//----------------------------------------------------------------------------------
// Method:      SetAxisProfile
// Description: This returns the scaled and curve profiled axis value for the specified axis
// Returns:     void
//----------------------------------------------------------------------------------
void DragonXbox::SetAxisProfile
(
	AXIS_IDENTIFIER         axis,       // <I> - axis identifier to modify
	AXIS_SENSITIVITY_CURVE  curve       // <I> - the definition of the sensitivity
)
{
    if ( axis < MAX_XBOX_AXIS )             // valid axis
    {
        m_axisProfile[ axis ] = curve;
    }
}

//----------------------------------------------------------------------------------
// Method:      SetAxisScale
// Description: This returns the scaled and curve profiled axis value for the specified axis
// Returns:     void
//----------------------------------------------------------------------------------
void DragonXbox::SetAxisScale
(
    AXIS_IDENTIFIER    axis,       // <I> - axis identifier to modify
    float              scaleFactor // <I> - value  (0 < scale <= 1.0) to scale the axis value
)
{
    if ( axis < MAX_XBOX_AXIS )             // valid axis
    {
		float axisRange = LimitValue::ForceInRange(scaleFactor, 0.0, 1.0);
		m_axisScale[axis] = axisRange;
    }
}
