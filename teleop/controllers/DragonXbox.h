/*
 * DragonXbox.h
 *
 *========================================================================================================
 *
 * File Description:
 *
 * TODO:: Add documentation about what this class does
 *========================================================================================================*/

#ifndef SRC_TELEOP_CONTROLLERS_DRAGONXBOX_H_
#define SRC_TELEOP_CONTROLLERS_DRAGONXBOX_H_

#include <interfaces/IDragonController.h>
#include <XboxController.h>


using namespace frc;

class DragonXbox : public IDragonController
{
    public:
		//-------------------------------------------------------------------------------------------------
    	// Method:      <<Constructor>>
    	// Description: Create a DragonXbox object .
    	//-------------------------------------------------------------------------------------------------
    	DragonXbox
		(
			int 	port			// <I> - port ID the control is connected to
		);


        //getters
        //-------------------------------------------------------------------------------------------------
        // Method:      GetAxisValue
        // Description: Return the current value (between -1.0 and 1.0) for the requested axis.
        // Returns:     float   - current axis value
        //-------------------------------------------------------------------------------------------------
        float GetAxisValue
        (
            AXIS_IDENTIFIER    axis        // <I> - axis identifier to read
        ) const override;

        //-------------------------------------------------------------------------------------------------
        // Method:      IsButtonPressed
        // Description: Return whether the requested button is selected (true) or not (false)
        // Returns:     bool    true  - button is pressed
        //                      false - button is not pressed
        //-------------------------------------------------------------------------------------------------
        bool IsButtonPressed
        (
            BUTTON_IDENTIFIER    button         // <I> - button to check
        ) const override;


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
        void SetAxisProfile
        (
            AXIS_IDENTIFIER           	axis,       // <I> - axis identifier to modify
            AXIS_SENSITIVITY_CURVE  	curve       // <I> - the definition of the sensitivity
        ) override;


        //-------------------------------------------------------------------------------------------------
        // Method:      SetAxisScale
        // Description: Scale the returned value to a range between the specified negative scale factor and
        //              the scale factor.  This is used to reduce the maximum value returned.
        //
        //              This affects values returned from GetAxis calls.
        // Returns:     void
        //-------------------------------------------------------------------------------------------------
        void SetAxisScale
        (
            AXIS_IDENTIFIER    			axis,       // <I> - axis identifier to modify
            float                       scaleFactor // <I> - value  (0 < scale <= 1.0) to scale the axis value
        ) override;


private:

        //-------------------------------------------------------------------------------------------------
        // Method:      <<Destructor>>
        // Description: Destroy a DragonXbox object .
        //-------------------------------------------------------------------------------------------------
        virtual ~DragonXbox() = default;

        // Methods not being implemented
        DragonXbox() = delete;
        DragonXbox( DragonXbox* other ) =  delete;

        // Attributes
        XboxController* 		m_xbox;

        // Allow 20 slots for the attributes (NOTE: it would be more efficient with vectors, but
        // we want to keep it simple)
        // Index into these arrays is AXIS_IDENTIFIER enum
        const int 				m_maxAxis = 20;          	// used for validation to make sure we don't walk off the array's memory
        float  					m_axisScale[20];            // scale factor used to limit the range of axis values returned
        float  					m_axisInversionFactor[20];  // scale factors used to invert the axis values (always 1.0 or -1.0)
        AXIS_SENSITIVITY_CURVE  m_axisProfile[20];          // the definition for "scaling" the axis values
};

#endif /* SRC_TELEOP_CONTROLLERS_DRAGONXBOX_H_ */
