/*
 * MechanismFactory.cpp
 */

#include <factories/MechanismFactory.h>
#include <interfaces/IMechanism.h>
#include <vector>

#include <subsys/components/DragonAnalogInput.h>
#include <subsys/components/DragonDigitalInput.h>
#include <subsys/components/DragonServo.h>
#include <subsys/components/DragonSolenoid.h>
#include <subsys/components/DragonTalon.h>

#include <subsys/mechanisms/ActiveGrabber.h>
#include <subsys/mechanisms/Climber.h>
#include <subsys/mechanisms/Grabber.h>
#include <subsys/mechanisms/Lift.h>
#include <subsys/mechanisms/SideHanger.h>

MechanismFactory* MechanismFactory::m_mechanismFactory = nullptr;

MechanismFactory* MechanismFactory::GetMechanismFactory()
{
	if ( MechanismFactory::m_mechanismFactory == nullptr )
	{
		MechanismFactory::m_mechanismFactory = new MechanismFactory();
	}
	return MechanismFactory::m_mechanismFactory;
}

IMechanism* MechanismFactory::GetIMechanism
(
	IMechanism::MECHANISM_TYPE			type		// <I> - manipulator type
)
{
	IMechanism* subsys = nullptr;
    switch ( type )
    {
        case IMechanism::CLIMBER:
            subsys = m_climber;
            break;

        case IMechanism::GRABBER:
            subsys = m_grabber;
            break;

        case IMechanism::LIFT:
            subsys = m_lift;
            break;

        case IMechanism::SIDE_HANGER:
            subsys = m_sidehanger;
            break;


        case IMechanism::ACTIVE_GRABBER:
            subsys = m_activeGrabber;
            break;

        default:
            printf( "==>> Unknown mechanism %d \n", type );
            break;
    }

	return subsys;
}

//=======================================================================================
// Method:  		CreateMechanism
// Description:		Create a mechanism from the inputs
// Returns:         Void
//=======================================================================================
IMechanism* MechanismFactory::CreateMechanism
(
    IMechanism::MECHANISM_TYPE              type,               // <I> - manipulator Type
    const DragonTalonVector&                motorControllers,   // <I> - Motor Controllers
    const DragonSolenoidVector&             solenoids,          // <I> - Solenoids
    const DragonDigitalInputVector&         digitalInputs,      // <I> - Digital Inputs
    const DragonAnalogInputVector&          analogInputs,       // <I> - Analog Inputs
    const DragonServoVector&                servos              // <I> - servos
)
{
    IMechanism* subsys = nullptr;
    int index = type;

    switch ( index )
    {
        case IMechanism::CLIMBER:
            subsys = new Climber( type, motorControllers, solenoids, digitalInputs, analogInputs, servos );
            m_climber = subsys;
            break;

        case IMechanism::GRABBER:
            subsys = new Grabber( type, motorControllers, solenoids, digitalInputs, analogInputs, servos );
            m_grabber = subsys;
            break;

        case IMechanism::LIFT:
            subsys = new Lift( type, motorControllers, solenoids, digitalInputs, analogInputs, servos );
            m_lift = subsys;
            break;

        case IMechanism::SIDE_HANGER:
            subsys = new SideHanger( type, motorControllers, solenoids, digitalInputs, analogInputs, servos );
            m_sidehanger = subsys;
            break;

        case IMechanism::ACTIVE_GRABBER:
            subsys = new ActiveGrabber( type, motorControllers, solenoids, digitalInputs, analogInputs, servos );
            m_activeGrabber = subsys;
            break;

        default:
            printf( "==>> Unknown mechanism %d \n", index );
            break;
    }


    return subsys;
}

MechanismFactory::MechanismFactory() : m_lift( nullptr ),
                                       m_grabber( nullptr ),
                                       m_climber( nullptr ),
                                       m_sidehanger( nullptr ),  //m_mechanisms()
                                       m_activeGrabber( nullptr )
{
//	m_mechanisms.resize( IMechanism::MAX_MECHANISM_TYPES );
//	for ( auto inx=0; inx<IMechanism::MAX_MECHANISM_TYPES; ++inx )
//	{
//		m_mechanisms[inx] = nullptr;
//	}
}

MechanismFactory::~MechanismFactory()
{
    delete m_lift;
    delete m_grabber;
    delete m_climber;
    delete m_sidehanger;

//	for ( auto inx=0; inx<IMechanism::MAX_MECHANISM_TYPES; ++inx )
//	{
//		if ( m_mechanisms[inx] != nullptr )
//		{
//			delete m_mechanisms[inx];
//		}
//	}
}

