/*
 * CubeToScale.h
 */

#ifndef SRC_TELEOP_CONTROLMECHANISMS_CUBETOSCALE_H_
#define SRC_TELEOP_CONTROLMECHANISMS_CUBETOSCALE_H_


// Team302 includes
#include <interfaces/ICubeHandler.h>
#include <teleop/controllers/TeleopControl.h>
#include <subsys/mechanisms/Grabber.h>
#include <subsys/mechanisms/Lift.h>
#include <teleop/controlMechanisms/CubeHandler.h>

class CubeToScale : public ICubeHandler
{
	public:
		CubeToScale();
		virtual ~CubeToScale() = default;

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

#endif /* SRC_TELEOP_CONTROLMECHANISMS_CUBETOSCALE_H_ */
