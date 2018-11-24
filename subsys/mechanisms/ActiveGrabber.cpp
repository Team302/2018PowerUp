/*
 * ActiveGrabber.cpp
 *
 */

#include <factories/MechanismFactory.h>
#include <factories/LidarFactory.h>
#include <vector>

#include <subsys/components/DragonAnalogInput.h>
#include <subsys/components/DragonDigitalInput.h>
#include <subsys/components/DragonServo.h>
#include <subsys/components/DragonSolenoid.h>
#include <subsys/components/DragonTalon.h>
#include <subsys/components/DragonLidar.h>
#include <interfaces/IMechanism.h>

#include <subsys/mechanisms/ActiveGrabber.h>

ActiveGrabber::ActiveGrabber
(
        IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
        const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
        const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
        const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
        const DragonAnalogInputVector&      analogInputs,       // <I> - Analog Inputs
        const DragonServoVector&            servos              // <I> - servos
) : m_grabSolenoid( nullptr ),
    m_grabClutchSolenoid( nullptr ),
    m_cubePresent( nullptr ),
    m_wheels( nullptr )
{
    LidarFactory* factory = LidarFactory::GetLidarFactory();
    if ( factory != nullptr )
    {
        m_cubePresent = factory->GetLidar( DragonLidar::FORWARD_GRABBER );
    }

//    printf( " creating active grabber \n" );
    if ( motorControllers.size() > 0 )
    {
        DragonTalon::TALON_TYPE mType= motorControllers[0]->GetType();
        if ( mType == DragonTalon::ACTIVE_INTAKE_WHEELS )
        {
//            printf( "adding intake wheels \n");
            m_wheels = motorControllers[0];
            m_wheels->SetControlMode( DragonTalon::PERCENT );
        }
    }

    for ( unsigned int inx=0; inx<solenoids.size(); ++inx )
    {
//        printf( "==> solenoids [ %d ] = %d \n", inx, solenoids[inx]->GetType() );
        switch ( solenoids[inx]->GetType() )
        {
        case DragonSolenoid::GRABBER_CLUTCH:
            m_grabClutchSolenoid = solenoids[inx];
//            printf( "got clutch \n");
            break;

        case DragonSolenoid::GRABBER_POSITION:
//            printf( "got grab \n");
            m_grabSolenoid = solenoids[inx];
            break;

        default:
            break;
        }
    }
}

ActiveGrabber::~ActiveGrabber()
{
}


IMechanism::MECHANISM_TYPE ActiveGrabber::GetType() const
{
    return IMechanism::ACTIVE_GRABBER;
}

void ActiveGrabber::SpinWheels
(
     double   power
)
{
    if ( m_wheels != nullptr )
    {
         m_wheels->Set( power );
    }
}

void ActiveGrabber::CloseActiveGrabber( bool close )
{
    if ( m_grabClutchSolenoid != nullptr )
    {
        m_grabClutchSolenoid->Set( close );
//        printf("ActiveGrabber closed or opened \n");
    }
}

void ActiveGrabber::WiggleCube()
{
	if (m_cubePresent != nullptr)
	{
		if (m_cubePresent->GetDistance() < 7.0)
		{
			m_wheels->Set(-0.2);
		}
		else
		{
			m_wheels->Set(0.1);
		}
	}
	else
	{
		m_wheels->Set( 0.0 );
	}
}

bool ActiveGrabber::GetCubePresent()
{
	return ( m_cubePresent->GetDistance() < 9.0 );
}


