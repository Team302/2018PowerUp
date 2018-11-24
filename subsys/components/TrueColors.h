/*
 * TrueColorsNew.h
 *
 *  Created on: Jan 17, 2018
 *      Author: casti
 */

#ifndef SUBSYS_XMLPARSING_TRUECOLORSNEW_H_
#define SUBSYS_XMLPARSING_TRUECOLORSNEW_H_

#include <CANLight.h>

using namespace mindsensors;

class TrueColors
{


	public:
		enum LightModes //Light modes for some actions for the CANLight LEDs
		{
			CUBE_TARGET_ACQUIRED,
			CLIMBING_SCALE,
			NORMAL_MODE,
			START_UP_SHOWOFF,
			TRANSITION_TO_TELEOP,
			HUMAN_PLAYER_SIGNAL,
			DISABLED_MODE
		};

        TrueColors() = delete;
        TrueColors( int canID );
        virtual ~TrueColors();


		//-----------------------------------------------------------------------------------
		// Method: SetLightMode
		// Function: To change between light modes for the CANLight LEDs.
		//
		//
		//
		// Returns: void
		//------------------------------------------------------------------------------------
		void SetLightMode
		(
			LightModes mode
		);
	private:
		CANLight* m_lights;
};

#endif /* SUBSYS_XMLPARSING_TRUECOLORSNEW_H_ */
