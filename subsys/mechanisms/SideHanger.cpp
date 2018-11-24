/*
 * SideHanger.cpp
 *
 */

#include <factories/MechanismFactory.h>
#include <interfaces/IMechanism.h>
#include <vector>

#include <subsys/components/DragonAnalogInput.h>
#include <subsys/components/DragonDigitalInput.h>
#include <subsys/components/DragonSolenoid.h>
#include <subsys/components/DragonServo.h>
#include <subsys/components/DragonTalon.h>
#include <subsys/mechanisms/SideHanger.h>


SideHanger::SideHanger
(
        IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
        const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
        const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
        const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
        const DragonAnalogInputVector&      analogInputs,       // <I> - Analog Inputs
        const DragonServoVector&            servos              // <I> - servos
) : m_spinMotor( nullptr ),
    m_latch( nullptr )
 //   m_release( nullptr )
{
    if ( motorControllers.size() == 1 )
    {
        DragonTalon::TALON_TYPE type = motorControllers[0]->GetType();
        if ( type == DragonTalon::SIDE_HANGER_MOTOR )
        {
            m_spinMotor = motorControllers[0];
        }
    }

    if ( solenoids.size() == 1 )
    {
        DragonSolenoid::DRAGON_SOLENOID_USAGE usage = solenoids[0]->GetType();
        if ( usage == DragonSolenoid::SIDEHANGER_LATCH )
        {
            m_latch = solenoids[0];
        }
    }

//    if ( servos.size() == 1 )
//    {
//        DragonServo::SERVO_USAGE usage = servos[0]->GetUsage();
//        if ( usage == DragonServo::SERVO_SIDEBAR_RELEASE_1 )
//        {
//            m_release = servos[0];
//        }
//    }

//    if ( m_release != nullptr )
//    {
//        printf( "==>> moving to min angle \n");
//    	m_release->MoveToMinAngle();
//    }

    if ( m_latch == nullptr )
    {
        printf( "==>> SideHanger:  missing latch \n" );
    }

    if ( m_spinMotor == nullptr )
    {
        printf( "==>> SideHanger:  missing motor \n" );
    }

//    if ( m_release == nullptr )
//    {
//        printf( "==>> SideHanger:  missing release servo \n" );
//    }

}

SideHanger::~SideHanger()
{
    delete m_spinMotor;
    delete m_latch;
}

IMechanism::MECHANISM_TYPE SideHanger::GetType() const
{
    return IMechanism::SIDE_HANGER;
}

void SideHanger::RaiseBar
(
    SIDEBAR_MOVE_DIRECTION  moveDirection               // <I> - Direction to move arm
)
{
    float speed = m_stopSpeed;
    switch ( moveDirection )
    {
        case CLOCKWISE:
            speed = m_cwSpeed;
            break;

        case COUNTER_CLOCKWISE:
            speed = m_ccwSpeed;
            break;

        default:
            speed = m_stopSpeed;
            break;
    }
    m_spinMotor->Set( speed );
}

void SideHanger::MoveBar(float speed)
{
	m_spinMotor->Set(speed);
}

void SideHanger::LatchBar
(
    bool    latch                                       // <I> - true = extend, false = retract
)
{
//    m_latch->Set( latch );
}

bool SideHanger::IsLatchExtended() const
{
//    return m_latch->Get();
	return true;
}


void SideHanger::ReleaseTrident() const
{
//    printf( "==>> SideHanger: target servo angle %g \n", m_releaseAngle );
//    printf( "==>> SideHanger: current servo angle %g \n", m_release->GetAngle() );
 //   m_release->SetAngle( m_releaseAngle );
 //   m_release->Set( 0.5 );
//    printf( "==>> moving to max angle \n");
//    m_release->MoveToMaxAngle();
}

