/*
 * DragonStick.cpp
 */

#include <stdio.h>

#include <Joystick.h>
#include <GenericHID.h>
#include <interfaces/IDragonController.h>

#include <SmartDashboard/SmartDashboard.h>  	// Smart Dashboard
#include <teleop/controllers/DragonStick.h>
#include <utils/LimitValue.h>

#include <cmath>        // std:abs

using namespace frc;


DragonStick::DragonStick
(
	int 	port			// <I> - port ID the control is connected to
) : IDragonController(),
	m_joystick( new Joystick( port ) ),
	m_axisScale(),
	m_axisInversionFactor(),
	m_axisProfile()
{
    // verify we have enough axis slots and if we don't write a message to the log file
    if ( (MAX_JOYSTICK_AXIS - MAX_XBOX_AXIS ) > m_maxAxis )
    {
    	SmartDashboard::PutString( "Axis Error", "Houston we have a problem ... there are more Joystick axis than we have array slots \n" );
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
	//	m_axisInversionFactor[XBOX_Y_AXIS_LEFT_JOYSTICK] = INVERT_AXIS;
	//	m_axisInversionFactor[XBOX_Y_AXIS_RIGHT_JOYSTICK] = INVERT_AXIS;
}

DragonStick::~DragonStick()
{
    delete m_joystick;
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
float DragonStick::GetAxisValue
(
    AXIS_IDENTIFIER    axis        // <I> - axis identifier to read
) const
{
    double output = 0.0;    //zero output to start
    if ( axis > MAX_XBOX_AXIS && axis < MAX_JOYSTICK_AXIS )
    {
    	int index = axis - MAX_XBOX_AXIS;
        // read the appropriate value from the xbox controller & multiply it by the inversion factor
        switch ( axis )
        {
            case JOYSTICK_X_AXIS:
                output = m_joystick->GetX() * m_axisInversionFactor[ index ];
//                output = m_joystick->GetAxis( Joystick::kXAxis ) * m_axisInversionFactor[ index ];
                break;
			case JOYSTICK_Y_AXIS:
			    output = m_joystick->GetY() * m_axisInversionFactor[ index ];
 //               output = m_joystick->GetAxis( Joystick::kYAxis ) * m_axisInversionFactor[ index ];
                break;

            case JOYSTICK_Z_AXIS:
                output = m_joystick->GetZ() * m_axisInversionFactor[ index ];
//                output = m_joystick->GetAxis( Joystick::kZAxis ) * m_axisInversionFactor[ index ];
                break;

            case JOYSTICK_TWIST_AXIS:
                output = m_joystick->GetTwist() * m_axisInversionFactor[ index ];
 //           	output = m_joystick->GetAxis( Joystick::kTwistAxis ) * m_axisInversionFactor[ index ];
            	break;

			case JOYSTICK_THROTTLE_AXIS:
                output = m_joystick->GetThrottle() * m_axisInversionFactor[ index ];
//                output = m_joystick->GetAxis( Joystick::kThrottleAxis ) * m_axisInversionFactor[ index ];
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
bool DragonStick::IsButtonPressed
(
    BUTTON_IDENTIFIER    button         // <I> - button to check
) const
{
    bool pressed = false;
    //switch statement to check if button is pressed depending on which button is identified

    switch(button)
    {
        case JOYSTICK_TRIGGER_BUTTON:
            pressed = m_joystick->GetTrigger();
            break;
		case JOYSTICK_TOP_BUTTON:
            pressed = m_joystick->GetTop();
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
void DragonStick::SetAxisProfile
(
	AXIS_IDENTIFIER         axis,       // <I> - axis identifier to modify
	AXIS_SENSITIVITY_CURVE  curve       // <I> - the definition of the sensitivity
)
{
	int index = axis - MAX_XBOX_AXIS;
    if ( index < m_maxAxis )             // valid axis
    {
        m_axisProfile[ index ] = curve;
    }
}

//----------------------------------------------------------------------------------
// Method:      SetAxisScale
// Description: This returns the scaled and curve profiled axis value for the specified axis
// Returns:     void
//----------------------------------------------------------------------------------
void DragonStick::SetAxisScale
(
    AXIS_IDENTIFIER    axis,       // <I> - axis identifier to modify
    float              scaleFactor // <I> - value  (0 < scale <= 1.0) to scale the axis value
)
{
	int index = axis - MAX_XBOX_AXIS;
    if ( index < m_maxAxis )             // valid axis
    {
		float axisRange = LimitValue::ForceInRange(scaleFactor, 0.0, 1.0);
		m_axisScale[index] = axisRange;
    }
}
