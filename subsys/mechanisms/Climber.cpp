/*
 * Climber.cpp
 *
 */

#include <factories/MechanismFactory.h>
#include <interfaces/IMechanism.h>
#include <vector>

#include <subsys/components/DragonAnalogInput.h>
#include <subsys/components/DragonDigitalInput.h>
#include <subsys/components/DragonServo.h>
#include <subsys/components/DragonSolenoid.h>
#include <subsys/components/DragonTalon.h>
#include <subsys/mechanisms/Climber.h>


Climber::Climber
(
        IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
        const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
        const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
        const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
        const DragonAnalogInputVector&      analogInputs,       // <I> - Analog Inputs
        const DragonServoVector&            servos              // <I> - servos
) : m_climbMotor( nullptr ),
    m_holdTarget( 0.0 )
{
    if ( motorControllers.size() > 0 )
    {
        DragonTalon::TALON_TYPE type = motorControllers[0]->GetType();
        if ( type == DragonTalon::CLIMBER_MASTER )
        {
            m_climbMotor = motorControllers[0];
        }
    }
    if ( m_climbMotor == nullptr )
    {
        printf( "==>> Climber: no motor definition \n" );
    }
}

Climber::~Climber()
{
    delete m_climbMotor;
}


IMechanism::MECHANISM_TYPE Climber::GetType() const
{
    return IMechanism::CLIMBER;
}

void Climber::RunWinch()
{
    m_climbMotor->SetControlMode( DragonTalon::PERCENT );
    m_climbMotor->Set( m_climbSpeed );
}

void Climber::HoldWinch()
{
	m_climbMotor->SetControlMode( DragonTalon::PERCENT );
	m_climbMotor->Set( m_holdSpeed );
}
void Climber::StopWinch()
{
    m_climbMotor->SetControlMode( DragonTalon::PERCENT );
    m_climbMotor->Set( m_stopSpeed );
}

void Climber::ReverseWinch()
{
	m_climbMotor->SetControlMode( DragonTalon::PERCENT );
	m_climbMotor->Set( -1 ); //Run max speed in reverse
}

void Climber::SaveHoldTarget()
{
    m_holdTarget = m_climbMotor->GetRotationCount();
    m_climbMotor->SetControlMode( DragonTalon::POSITION );
    m_climbMotor->SetClosedLoopParams( 0, m_hold_kP, m_hold_kI, m_hold_kD, m_hold_kF, 0 );

}
void Climber::HoldPosition()
{
    m_climbMotor->Set( m_holdTarget );
}

bool Climber::IsClimbing()
{
	return ( std::abs(m_climbSpeed) > 0.01 );
}
