/*
 * ClimbHandler.h
 */

#ifndef SRC_TELEOP_CONTROLMECHANISMS_CLIMBHANDLER_H_
#define SRC_TELEOP_CONTROLMECHANISMS_CLIMBHANDLER_H_

#include <interfaces/IMechanism.h>
#include <interfaces/IMechanismControl.h>
#include <teleop/controllers/TeleopControl.h>

#include <subsys/mechanisms/Climber.h>
#include <subsys/mechanisms/SideHanger.h>


class ClimbHandler: public IMechanismControl
{
	public:
		ClimbHandler();
		virtual ~ClimbHandler();

		//-----------------------------------------------------------------------------------
		// Method:          Periodic
		// Description:     Run the mechanism
		// Returns:         void
		//-----------------------------------------------------------------------------------
		void Periodic() override;


	private:
	    TeleopControl*			m_controller;
	    Climber*				m_climber;
	    SideHanger*				m_sideHanger;
	    bool					m_winchPrevRun;
	    bool					m_tridentUnlocked;
	    bool					m_safetyPrevious;
};

#endif /* SRC_TELEOP_CONTROLMECHANISMS_CLIMBHANDLER_H_ */
