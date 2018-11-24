/*
 * ICubeHandler.h
 */

#ifndef SRC_INTERFACES_ICUBEHANDLER_H_
#define SRC_INTERFACES_ICUBEHANDLER_H_


class ICubeHandler
{
	public:

		enum CURRENT_CUBEHANDLER_STATE
		{
			BASE_HANDLER = -1,
			MOVE_TO_FLOOR_POS,
			MOVE_TO_SWITCH_POS,
			MOVE_TO_SCALE_POS,
			HOLD_POS,
			MANUAL_CONTROL
		};

		ICubeHandler() = default;
		virtual ~ICubeHandler() = default;

		//-----------------------------------------------------------------------------------
		// Method:          Periodic
		// Description:     Run the mechanism
	    // Returns:         ICubeHandler::CURRENT_CUBEHANDLER_STATE		next state to run
		//-----------------------------------------------------------------------------------
		virtual ICubeHandler::CURRENT_CUBEHANDLER_STATE Periodic() = 0;

};




#endif /* SRC_INTERFACES_ICUBEHANDLER_H_ */
