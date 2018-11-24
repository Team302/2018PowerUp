/*
 * Grabber.cpp
 *
 */

#include <factories/MechanismFactory.h>
#include <vector>

#include <subsys/components/DragonAnalogInput.h>
#include <subsys/components/DragonDigitalInput.h>
#include <subsys/components/DragonServo.h>
#include <subsys/components/DragonSolenoid.h>
#include <subsys/components/DragonTalon.h>
#include <interfaces/IMechanism.h>

#include <subsys/mechanisms/Grabber.h>

Grabber::Grabber
(
        IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
        const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
        const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
        const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
        const DragonAnalogInputVector&         analogInputs,       // <I> - Analog Inputs
        const DragonServoVector&            servos              // <I> - servos
) : m_grabSolenoid( nullptr ),
    m_grabClutchSolenoid( nullptr ),
	m_cubePresent( nullptr )
{
    if ( digitalInputs.size() == 1 )
    {
        DragonDigitalInput::DIGITAL_INPUT_TYPE type = digitalInputs[0]->GetType();
        if ( type == DragonDigitalInput::CUBE_PRESENT )
        {
            m_cubePresent = digitalInputs[0];
        }
    }

	for ( unsigned int inx=0; inx<solenoids.size(); ++inx )
	{
//		printf( "==> solenoids [ %d ] = %d \n", inx, solenoids[inx]->GetType() );
		switch ( solenoids[inx]->GetType() )
		{
		case DragonSolenoid::GRABBER_CLUTCH:
			m_grabClutchSolenoid = solenoids[inx];
			break;

		case DragonSolenoid::GRABBER_POSITION:
			m_grabSolenoid = solenoids[inx];
			break;

		default:
			break;
		}
	}
}

Grabber::~Grabber()
{
}


IMechanism::MECHANISM_TYPE Grabber::GetType() const
{
    return IMechanism::GRABBER;
}

void Grabber::SpinGrabber( bool close )
{
    m_grabClutchSolenoid->Set( close );
}

void Grabber::CloseGrabber( bool close )
{
    m_grabSolenoid->Set( close );
//    printf("grabber closed or opened \n");
}

bool Grabber::GetCubePresent()
{
//	return m_cubePresent->Get();
	return true;
}
