/*
 * CubeHandler.h
 */

#ifndef SRC_TELEOP_CONTROLMECHANISMS_CUBEHANDLER_H_
#define SRC_TELEOP_CONTROLMECHANISMS_CUBEHANDLER_H_

// Team302 includes
#include <interfaces/ICubeHandler.h>
#include <teleop/controllers/TeleopControl.h>
#include <subsys/mechanisms/ActiveGrabber.h>
#include <subsys/mechanisms/Grabber.h>
#include <subsys/mechanisms/Lift.h>

#include <teleop/controlMechanisms/CubeToFloor.h>
#include <teleop/controlMechanisms/CubeToSwitch.h>
#include <teleop/controlMechanisms/CubeToScale.h>
#include <teleop/controlMechanisms/CubeHoldPos.h>
#include <teleop/controlMechanisms/CubeManualControl.h>


class CubeHandler
{
	public:
		CubeHandler();
		virtual ~CubeHandler() = default;

	    //-----------------------------------------------------------------------------------
	    // Method:          Periodic
	    // Description:     Run the mechanism
	    // Returns:         void
	    //-----------------------------------------------------------------------------------
		void Periodic();

	    void SetState
		(
				ICubeHandler::CURRENT_CUBEHANDLER_STATE	state
		);

	    void ResetHeight();

	private:
	    TeleopControl*								m_controller;
	    Grabber*									m_grabber;
	    ActiveGrabber*                              m_activeGrabber;
        Lift*                   					m_lift;
	    ICubeHandler::CURRENT_CUBEHANDLER_STATE		m_currentState;

	    const float 								DEAD_BAND = 0.2;
	    bool 										m_dbPassed; // deadband passed
	    bool 										m_safetyToggle;
	    bool 										m_prevBackButton;
	    bool										m_fourBarState; //do we want it up or down
};

#endif /* SRC_TELEOP_CONTROLMECHANISMS_CUBEHANDLER_H_ */
