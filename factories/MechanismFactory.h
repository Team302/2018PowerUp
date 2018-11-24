/*
 * MechanismFactory.h
 */

#ifndef SRC_FACTORIES_MECHANISMFACTORY_H_
#define SRC_FACTORIES_MECHANISMFACTORY_H_

#include <interfaces/IMechanism.h>
#include <vector>

#include <subsys/components/DragonAnalogInput.h>
#include <subsys/components/DragonDigitalInput.h>
#include <subsys/components/DragonServo.h>
#include <subsys/components/DragonSolenoid.h>
#include <subsys/components/DragonTalon.h>

class MechanismFactory
{
	public:

		static MechanismFactory* GetMechanismFactory();


		IMechanism* GetIMechanism
		(
			IMechanism::MECHANISM_TYPE			type		// <I> - manipulator type
		);

		//=======================================================================================
		// Method:  		CreateManipulator
		// Description:		Create a manipulator from the inputs
		// Returns:         Void
		//=======================================================================================
		IMechanism* CreateMechanism
		(
			IMechanism::MECHANISM_TYPE		        type,				// <I> - manipulator Type
			const DragonTalonVector&			    motorControllers,	// <I> - Motor Controllers
			const DragonSolenoidVector&		        solenoids,			// <I> - Solenoids
			const DragonDigitalInputVector&         digitalInputs,      // <I> - Digital Inputs
			const DragonAnalogInputVector&          analogInputs,       // <I> - Analog Inputs
			const DragonServoVector&                servos              // <I> - servos
		);


	private:
		MechanismFactory();
		virtual ~MechanismFactory();

		IMechanism*                 m_lift;
		IMechanism*                 m_grabber;
		IMechanism*                 m_climber;
		IMechanism*                 m_sidehanger;
		IMechanism*                 m_activeGrabber;

		static MechanismFactory*	m_mechanismFactory;
//		IMechanismVector            m_mechanisms;


};

#endif /* SRC_FACTORIES_MECHANISMFACTORY_H_ */
