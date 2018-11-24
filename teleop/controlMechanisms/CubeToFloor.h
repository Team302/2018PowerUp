/*
 * CubeToFloor.h
 */

#ifndef SRC_TELEOP_CONTROLMECHANISMS_CUBETOFLOOR_H_
#define SRC_TELEOP_CONTROLMECHANISMS_CUBETOFLOOR_H_


// Team302 includes
#include <interfaces/ICubeHandler.h>
#include <teleop/controlMechanisms/CubeHandler.h>
#include <teleop/controllers/TeleopControl.h>
#include <subsys/mechanisms/Grabber.h>
#include <subsys/mechanisms/Lift.h>

class CubeToFloor  : public ICubeHandler
{
	public:
		CubeToFloor();
		virtual ~CubeToFloor() = default;

		//-----------------------------------------------------------------------------------
		// Method:          Periodic
		// Description:     Run the mechanism
	    // Returns:         ICubeHandler::CURRENT_CUBEHANDLER_STATE		next state to run
		//-----------------------------------------------------------------------------------
		ICubeHandler::CURRENT_CUBEHANDLER_STATE Periodic() override;


	private:
		TeleopControl*			m_controller;
		Lift*					m_lift;
};

#endif /* SRC_TELEOP_CONTROLMECHANISMS_CUBETOFLOOR_H_ */
