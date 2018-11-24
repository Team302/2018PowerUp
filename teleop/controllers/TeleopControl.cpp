/*========================================================================================================
 * OperatorInterface.cpp
 *========================================================================================================
 *
 * File Description:
 *
 * This implements holds onto the instances of the game controllers used by driver and the co-pilot.
 *========================================================================================================*/
// FRC Includes
#include <GenericHID.h>
#include <interfaces/IDragonController.h>
#include <teleop/controllers/DragonStick.h>
#include <teleop/controllers/TeleopControl.h>
#include <DriverStation.h>
#include <cstdio>

using namespace frc;

//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of this class, it will create one.  The
//              single class instance will be returned.
// Returns:     OperatorInterface*  instance of this class
//----------------------------------------------------------------------------------
TeleopControl* TeleopControl::m_instance = nullptr; // initialize the instance variable to nullptr
TeleopControl* TeleopControl::GetInstance()
{
    if ( TeleopControl::m_instance == nullptr )
    {
        TeleopControl::m_instance = new TeleopControl();
    }
    return TeleopControl::m_instance;
}
//----------------------------------------------------------------------------------
// Method:      OperatorInterface <<constructor>>
// Description: This will construct and initialize the object.
//              It maps the functions to the buttons/axis.
//---------------------------------------------------------------------------------
TeleopControl::TeleopControl() : m_axisIDs(),
								 m_buttonIDs(),
								 m_controllerIndex(),
								 m_controllers(),
								 m_count( 0 )
{
	DriverStation* ds = &DriverStation::GetInstance();
	for ( int inx=0; inx<DriverStation::kJoystickPorts; ++inx )
	{
		m_controllers[inx] = nullptr;
		if ( ds->GetJoystickIsXbox( inx ) )
		{
			m_controllers[inx] = new DragonXbox( inx );
		}
		else if ( ds->GetJoystickType( inx ) == GenericHID::kHIDJoystick )
		{
			m_controllers[inx] = new DragonStick( inx );
		}
	}


    // Initialize the items to not defined
    for ( int inx=0; inx<m_maxFunctions; ++inx )
    {
        m_axisIDs[inx]    		= UNDEFINED_AXIS;
        m_buttonIDs[inx]  		= UNDEFINED_BUTTON;
        m_controllerIndex[inx]  = -1;
    }

//	for ( int inx=0; inx<6; ++inx )
//	{
//		printf( "==>> joystick %d type %d \n", inx, ds->GetJoystickType( inx ) );
//	}

    if ( m_controllers[0] != nullptr && ds->GetJoystickIsXbox(0) )
    {
    	if ( ds->GetJoystickIsXbox(0) )
    	{
			m_controllerIndex[ TANK_DRIVE_LEFT_CONTROL ] 	= 0;
			m_axisIDs[ TANK_DRIVE_LEFT_CONTROL ]    		= XBOX_Y_AXIS_LEFT_JOYSTICK;
			m_controllerIndex[ TANK_DRIVE_RIGHT_CONTROL ] 	= 0;
			m_axisIDs[ TANK_DRIVE_RIGHT_CONTROL ]   		= XBOX_Y_AXIS_RIGHT_JOYSTICK;

			m_controllerIndex[ ARCADE_DRIVE_THROTTLE ] 		= 0;
			m_axisIDs[ ARCADE_DRIVE_THROTTLE ]      		= XBOX_Y_AXIS_LEFT_JOYSTICK;
			m_controllerIndex[ ARCADE_DRIVE_STEER ] 		= 0;
			m_axisIDs[ ARCADE_DRIVE_STEER ]         		= XBOX_X_AXIS_RIGHT_JOYSTICK;

			m_controllerIndex[ ROBOT_X_MAGNITUDE ]			= 0;
			m_axisIDs[ ROBOT_X_MAGNITUDE ]    				= XBOX_X_AXIS_LEFT_JOYSTICK;

			m_controllerIndex[ ROBOT_Y_MAGNITUDE ]			= 0;
			m_axisIDs[ ROBOT_Y_MAGNITUDE ]    				= XBOX_Y_AXIS_LEFT_JOYSTICK;

			m_controllerIndex[ ROBOT_ROTATION_MAGNITUDE ]	= 0;
			m_axisIDs[ ROBOT_ROTATION_MAGNITUDE ]    		= XBOX_X_AXIS_RIGHT_JOYSTICK;

			m_controllerIndex[ SWITCH_DRIVE_MODE ]          = 0;
			m_buttonIDs[ SWITCH_DRIVE_MODE ]                = XBOX_A_BUTTON;

//			m_controllerIndex[ TELEOP_HOLD_POSITION ]		= 0;
//			m_buttonIDs[ TELEOP_HOLD_POSITION ]				= XBOX_RIGHT_TRIGGER;
    	}
		else if ( ds->GetJoystickType( 0 ) == GenericHID::kHIDJoystick )
		{
			printf( "need to map DragonStick functions 0 \n" );
		}
    }
    else
    {
    	printf( "TeleopControl::TeleopControl(): no controller plugged into port 0 \n" );
    }

    if ( m_controllers[1] != nullptr && ds->GetJoystickIsXbox(1) )
    {
        // cubes
        m_controllerIndex[ GRAB_CUBE ]                  = 1;
        m_buttonIDs[ GRAB_CUBE ]                        = XBOX_RIGHT_BUMPER; //XBOX_LEFT_BUMPER

        m_controllerIndex[ RAISE_4BAR ]                 = 1;
        m_buttonIDs[ RAISE_4BAR ]                       = XBOX_POV_0_PRESSED; //XBOX_RIGHT_BUMPER

        m_controllerIndex[ LOWER_4BAR ]                 = 1;
        m_buttonIDs[ LOWER_4BAR ]						= XBOX_POV_180_PRESSED;

        m_controllerIndex[ MANUAL_ELEVATOR_CONTROL ]    = 1;
        m_axisIDs[ MANUAL_ELEVATOR_CONTROL ]            = XBOX_Y_AXIS_LEFT_JOYSTICK;

        m_controllerIndex[ INTAKE_CUBE ]                = 1;
        m_axisIDs[ INTAKE_CUBE ]                        = XBOX_Y_AXIS_RIGHT_JOYSTICK;

        m_controllerIndex[ TOGGLE_SAFTEY_SWITCH ]		= 1;
        m_buttonIDs[ TOGGLE_SAFTEY_SWITCH ]				= XBOX_START_BUTTON;

        // side hanger
        m_controllerIndex[ ROTATE_SIDE_CLIMB_BAR_CW ]   = 1;
        m_axisIDs[ ROTATE_SIDE_CLIMB_BAR_CW ]         	= XBOX_LEFT_TRIGGER;
        m_controllerIndex[ ROTATE_SIDE_CLIMB_BAR_CCW ]  = 1;
        m_axisIDs[ ROTATE_SIDE_CLIMB_BAR_CCW ]        	= XBOX_RIGHT_TRIGGER;

//        m_controllerIndex[ EXTEND_CLIMB_LATCH ]         = 1;
//        m_buttonIDs[ EXTEND_CLIMB_LATCH ]               = XBOX_X_BUTTON;
//        m_controllerIndex[ RETRACT_CLIMB_LATCH ]        = 1;
//        m_buttonIDs[ RETRACT_CLIMB_LATCH ]              = XBOX_B_BUTTON;
        m_controllerIndex[ RELEASE_SIDE_HANGER ]        = 1;
        m_buttonIDs[ RELEASE_SIDE_HANGER ]              = XBOX_BACK_BUTTON;

        // climber
        m_controllerIndex[ RETRACT_WINCH ]              = 1;
        m_buttonIDs[ RETRACT_WINCH ]                    = XBOX_Y_BUTTON;

        // hold climber
        m_controllerIndex[ HOLD_ROBOT_CLIMB ]			= 1;
        m_buttonIDs[ HOLD_ROBOT_CLIMB ]					= XBOX_B_BUTTON;

        // reverse climber
        m_controllerIndex[ UNRETRACT_WINCH ]            = 1;
        m_buttonIDs[ UNRETRACT_WINCH ]                  = XBOX_A_BUTTON;

        m_controllerIndex[ HUMAN_PLAYER_SIGNAL ]		= 1;
        m_buttonIDs[ HUMAN_PLAYER_SIGNAL ]				= XBOX_PRESS_RIGHT_STICK;

        m_controllerIndex[ WIGGLE_CUBE ]				= 1;
        m_buttonIDs[ WIGGLE_CUBE ]						= XBOX_POV_90_PRESSED;
    }
    else
    {
    	printf( "TeleopControl::TeleopControl(): no controller plugged into port 1 \n" );
    }

    if ( m_controllers[2] != nullptr && ds->GetJoystickIsXbox(2) )
        {
            // 4bar motor (testing)
            m_controllerIndex[ MANUAL_MOVE_4BAR_MOTOR ]        = 2;
            m_axisIDs[ MANUAL_MOVE_4BAR_MOTOR ]                = XBOX_Y_AXIS_RIGHT_JOYSTICK;


        }
        else
        {
        	printf( "TeleopControl::TeleopControl(): no controller plugged into port 2 \n" );
       }
}


//------------------------------------------------------------------
// Method:      SetAxisScaleFactor
// Description: Allow the range of values to be set smaller than
//              -1.0 to 1.0.  By providing a scale factor between 0.0
//              and 1.0, the range can be made smaller.  If a value
//              outside the range is provided, then the value will
//              be set to the closest bounding value (e.g. 1.5 will
//              become 1.0)
// Returns:     void
//------------------------------------------------------------------
void TeleopControl::SetAxisScaleFactor
(
    TeleopControl::FUNCTION_IDENTIFIER  	function,      // <I> - function that will update an axis
    float                                   scaleFactor    // <I> - scale factor used to limit the range
)
{
	int ctlIndex = m_controllerIndex[ function];
	AXIS_IDENTIFIER axis = m_axisIDs[ function ];
    if ( ctlIndex > -1 && axis != UNDEFINED_AXIS  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		m_controllers[ ctlIndex ]->SetAxisScale( axis,scaleFactor);
    	}
    }
}

//------------------------------------------------------------------
// Method:      SetAxisProfile
// Description: Sets the axis profile for the specifed axis
// Returns:     void
//------------------------------------------------------------------
void TeleopControl::SetAxisProfile
(
    TeleopControl::FUNCTION_IDENTIFIER      function,       // <I> - function that will update an axis
    AXIS_SENSITIVITY_CURVE          		profile         // <I> - profile to use
)
{
	int ctlIndex = m_controllerIndex[ function];
	AXIS_IDENTIFIER axis = m_axisIDs[ function ];
    if ( ctlIndex > -1 && axis != UNDEFINED_AXIS  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		m_controllers[ ctlIndex ]->SetAxisProfile( axis,profile);
    	}
    }
}

//------------------------------------------------------------------
// Method:      GetAxisValue
// Description: Reads the joystick axis, removes any deadband (small
//              value) and then scales as requested.
// Returns:     float   -  scaled axis value
//------------------------------------------------------------------
float TeleopControl::GetAxisValue
(
    TeleopControl::FUNCTION_IDENTIFIER  function    // <I> - function that whose axis will be read
) const
{
    float value = 0.0;
	int ctlIndex = m_controllerIndex[ function];
	AXIS_IDENTIFIER axis = m_axisIDs[ function ];
    if ( ctlIndex > -1 && axis != UNDEFINED_AXIS  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		value = m_controllers[ ctlIndex ]->GetAxisValue( axis );
    	}
    }
/*
    if ( function == TeleopControl::RAISE_4BAR )
    {

        if ( m_count == 0  )
        {
//            printf( "==>> checking axis function %d \n", function );
//            printf( "==>> controller %d axis %d value %g \n", m_controllerIndex[ function ], m_axisIDs[ function ], value );
        }
        m_count++;
        if ( m_count > 100 )
        {
            m_count = 0;
        }
    }*/

    //	SmartDashboard::PutNumber( "Axis ID ", function );
//	SmartDashboard::PutNumber( "Axis Value ", value );
    return value;
}

//------------------------------------------------------------------
// Method:      IsButtonPressed
// Description: Reads the button value.  Also allows POV, bumpers,
//              and triggers to be treated as buttons.
// Returns:     bool   -  scaled axis value
//------------------------------------------------------------------
bool TeleopControl::IsButtonPressed
(
    TeleopControl::FUNCTION_IDENTIFIER  function    // <I> - function that whose button will be read
) const
{
    bool isSelected = false;
	int ctlIndex = m_controllerIndex[ function];
	BUTTON_IDENTIFIER btn = m_buttonIDs[ function ];
    if ( ctlIndex > -1 && btn != UNDEFINED_BUTTON  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		isSelected = m_controllers[ ctlIndex ]->IsButtonPressed( btn );
    	}
    }


/*    if ( function == TeleopControl::RAISE_4BAR )
    {

        if ( m_count == 0  )
        {
//            printf( "==>> checking button function %d \n", function );
//            printf( "==>> controller %d button %d pressed %s \n", m_controllerIndex[ function ], m_buttonIDs[ function ], isSelected ? "true" : "false" );
        }
        m_count++;
        if ( m_count > 100 )
        {
            m_count = 0;
        }
    }*/



    return isSelected;
}


