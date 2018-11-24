/*
 * LEDHandler.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Austin
 */

#ifndef SRC_TELEOP_CONTROLMECHANISMS_LEDHANDLER_H_
#define SRC_TELEOP_CONTROLMECHANISMS_LEDHANDLER_H_

// teleop stuff
#include <teleop/controllers/TeleopControl.h>
//Interface
#include <interfaces/IMechanism.h>
//Factories
#include <factories/MechanismFactory.h>
#include <factories/LEDFactory.h>
#include <factories/LidarFactory.h>
//Stuff we need
#include <subsys/components/TrueColors.h>
#include <subsys/mechanisms/ActiveGrabber.h>
#include <subsys/mechanisms/Grabber.h>
#include <subsys/mechanisms/Lift.h>
#include <subsys/mechanisms/Climber.h>
#include <subsys/components/DragonLidar.h>

class LEDHandler {
public:
	LEDHandler();
	virtual ~LEDHandler() = default;

    //-----------------------------------------------------------------------------------
    // Method:          Periodic
    // Description:     Run the mechanism
    // Returns:         void
    //-----------------------------------------------------------------------------------
	void TeleopLED();
	void AutonLED();
	void DisabledLED();

private:
	bool				m_ran;

	// colorz
	TrueColors* m_leds;
	// Mechanismz
	ActiveGrabber* 		m_activeGrabber;
	Grabber* 			m_grabber;
	Lift* 				m_lift;
	Climber*			m_climber;
	// Controller
	TeleopControl*		m_controller;

	//thos lidars (just one of them right now)
	DragonLidar* m_downLidar;

};

#endif /* SRC_TELEOP_CONTROLMECHANISMS_LEDHANDLER_H_ */
