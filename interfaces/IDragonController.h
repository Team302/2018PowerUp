/*
 * IDragonController.h
 *
 *  Created on: Dec 29, 2017
 *      Author: Team302
 */

#ifndef SRC_INTERFACES_IDRAGONCONTROLLER_H_
#define SRC_INTERFACES_IDRAGONCONTROLLER_H_


enum AXIS_IDENTIFIER
{
	UNDEFINED_AXIS = -1000,
	XBOX_X_AXIS_LEFT_JOYSTICK = 0,
	XBOX_Y_AXIS_LEFT_JOYSTICK,
	XBOX_LEFT_TRIGGER,
	XBOX_RIGHT_TRIGGER,
	XBOX_X_AXIS_RIGHT_JOYSTICK,
	XBOX_Y_AXIS_RIGHT_JOYSTICK,
	MAX_XBOX_AXIS,                   // used for looping
	JOYSTICK_X_AXIS,
	JOYSTICK_Y_AXIS,
	JOYSTICK_Z_AXIS,
	JOYSTICK_TWIST_AXIS,
	JOYSTICK_THROTTLE_AXIS,
	MAX_JOYSTICK_AXIS,
	GAMEPAD_AXIS_16,
	GAMEPAD_AXIS_17,
	GAMEPAD_DIAL_22,//Dial has 6 settings for axis. Dial setting 22 = highest, 27 = lowest.
	GAMEPAD_DIAL_23,
	GAMEPAD_DIAL_24,
	GAMEPAD_DIAL_25,
	GAMEPAD_DIAL_26,
	GAMEPAD_DIAL_27,
	MAX_GAMEPAD_AXIS
};

enum BUTTON_IDENTIFIER
{
	UNDEFINED_BUTTON = -1000,
	XBOX_A_BUTTON = 0,
	XBOX_B_BUTTON,
	XBOX_X_BUTTON,
	XBOX_Y_BUTTON,
	XBOX_LEFT_BUMPER,
	XBOX_RIGHT_BUMPER,
	XBOX_BACK_BUTTON,
	XBOX_START_BUTTON,
	XBOX_PRESS_LEFT_STICK,
	XBOX_PRESS_RIGHT_STICK,
	XBOX_LEFT_TRIGGER_PRESSED,
	XBOX_RIGHT_TRIGGER_PRESSED,
    XBOX_POV_0_PRESSED,
    XBOX_POV_45_PRESSED,
    XBOX_POV_90_PRESSED,
    XBOX_POV_135_PRESSED,
    XBOX_POV_180_PRESSED,
    XBOX_POV_225_PRESSED,
    XBOX_POV_270_PRESSED,
    XBOX_POV_315_PRESSED,
	MAX_XBOX_BUTTONS,                    // used for looping
	JOYSTICK_TRIGGER_BUTTON,
	JOYSTICK_TOP_BUTTON,
	MAX_JOYSTICK_BUTTONS,
	GAMEPAD_BUTTON_1,
	GAMEPAD_BUTTON_2,
	GAMEPAD_BUTTON_3,
	GAMEPAD_BUTTON_4,
	GAMEPAD_BUTTON_5,
	GAMEPAD_BUTTON_6,
	GAMEPAD_BUTTON_7,
	GAMEPAD_BUTTON_8,
	GAMEPAD_BUTTON_9,
	GAMEPAD_BUTTON_10,
	GAMEPAD_BUTTON_11,
	GAMEPAD_BUTTON_12,
	GAMEPAD_BUTTON_13,
	GAMEPAD_BIG_RED_BUTTON,
	GAMEPAD_SWITCH_18,
	GAMEPAD_SWITCH_19,
	GAMEPAD_SWITCH_20,
	GAMEPAD_SWITCH_21,
	GAMEPAD_BUTTON_14_UP,
	GAMEPAD_BUTTON_14_DOWN,
	GAMEPAD_BUTTON_15_UP,
	GAMEPAD_BUTTON_15_DOWN,
	MAX_GAMEPAD_BUTTONS
};


enum AXIS_SENSITIVITY_CURVE //enum for selecting linear or cubic axis profile
{
	AXIS_LINEAR ,
	AXIS_CUBIC,
	MAX_SENS_OPTIONS
};

class IDragonController
{
    public:

		IDragonController() = default;
		virtual ~IDragonController() = default;

        //getters
        //-------------------------------------------------------------------------------------------------
        // Method:      GetAxisValue
        // Description: Return the current value (between -1.0 and 1.0) for the requested axis.
        // Returns:     float   - current axis value
        //-------------------------------------------------------------------------------------------------
        virtual float GetAxisValue
        (
            AXIS_IDENTIFIER    axis        // <I> - axis identifier to read
        ) const = 0;

        //-------------------------------------------------------------------------------------------------
        // Method:      IsButtonPressed
        // Description: Return whether the requested button is selected (true) or not (false)
        // Returns:     bool    true  - button is pressed
        //                      false - button is not pressed
        //-------------------------------------------------------------------------------------------------
        virtual bool IsButtonPressed
        (
            BUTTON_IDENTIFIER    button         // <I> - button to check
        ) const = 0;


        //setters
        //-------------------------------------------------------------------------------------------------
        // Method:      SetAxisProfile
        // Description: Specify the profile curve used for setting the sensitivity of the axis.  By default,
        //              this is linear, but a cubic curve would give more control when the axis is barely
        //              pressed (e.g. if it were moved 50% forward, instead of returning 0.5, it would
        //              return 0.5 * 0.5 * 0.5 or .125, but when the axis was moved all the way forward,
        //              it would return the same value -- 1.0.  Since it is cubed, it retains the sign.
        //
        //              This affects values returned from GetAxis calls.
        // Returns:     void
        //-------------------------------------------------------------------------------------------------
        virtual void SetAxisProfile
        (
            AXIS_IDENTIFIER           axis,       // <I> - axis identifier to modify
            AXIS_SENSITIVITY_CURVE    curve       // <I> - the definition of the sensitivity
        ) = 0;


        //-------------------------------------------------------------------------------------------------
        // Method:      SetAxisScale
        // Description: Scale the returned value to a range between the specified negative scale factor and
        //              the scale factor.  This is used to reduce the maximum value returned.
        //
        //              This affects values returned from GetAxis calls.
        // Returns:     void
        //-------------------------------------------------------------------------------------------------
        virtual void SetAxisScale
        (
            AXIS_IDENTIFIER    			axis,       // <I> - axis identifier to modify
            float                       scaleFactor // <I> - value  (0 < scale <= 1.0) to scale the axis value
        ) = 0;


    protected:

        const float DEAD_BAND_THRESH = 0.2;         // Minimum value joystick must be past to actually return value to prevent drift
        const float TRIGGER_PRESSED_THRESH = 0.4;   // When triggers are treated as buttons, it must be pressed more than this value to be considered pressed
        const float DONT_INVERT_AXIS = 1.0;         // Scale factor for inverting the axis
        const float INVERT_AXIS = -1.0;             // Scale factor for inverting the axis
        const float LINEAR_SCALE_PROFILE = 1.0;     // Linear profile power
        const float CUBIC_SCALE_PROFILE = 3.0;      // Cubic profile power
        const float STD_RANGE_SCALING = 1.0;        // Range is between -1.0 and 1.0
};


#endif /* SRC_INTERFACES_IDRAGONCONTROLLER_H_ */
