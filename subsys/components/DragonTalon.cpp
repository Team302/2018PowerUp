/*
 * DragonTalon.cpp
 *
 */

#include <subsys/components/DragonTalon.h>
#include <factories/ChassisFactory.h>
#include <interfaces/IChassis.h>

#include <ctre/phoenix/ErrorCode.h>
#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>
#include <ctre/phoenix/MotorControl/ControlMode.h>
#include <cmath>


using namespace  ctre::phoenix;
using namespace  ctre::phoenix::motorcontrol;
using namespace  ctre::phoenix::motorcontrol::can;

//------------------------------------------------------------------------------
// Method:		<<constructor>>
// Description:	Since we have methods on the CANTalon that don't appear to be
// 				working, we have
//------------------------------------------------------------------------------
DragonTalon::DragonTalon
(
	DragonTalon::TALON_TYPE	deviceType,		// <I> - Usage of the motor
	int 					deviceID,		// <I> - CAN ID
	int						countsPerRev,   // <I> - counts per revolution for the encoder
	float					gearRatio		// <I> - gear ratio for encoder to output shaft
) : m_talon( new TalonSRX( deviceID ) ),
	m_type( deviceType ),
	m_zeroPos( 0.0 ),
	m_sensorInverted( false ),
	m_countsPerRev( countsPerRev ),
	m_gearRatio( gearRatio )
{
	m_talon->ClearStickyFaults(0 );
	m_talon->Set( ControlMode::PercentOutput, 0.0 );
}

//------------------------------------------------------------------------------
// Method:		GetType
// Description:	Return the talon's usage type
// Returns:		DragonTalon::TALON_TYPE			talon's type
//------------------------------------------------------------------------------
DragonTalon::TALON_TYPE DragonTalon::GetType() const
{
	return m_type;
}

//------------------------------------------------------------------------------
// Method:		GetCANID
// Description:	Return the talon's CAN ID
// Returns:		int			talon's CAN ID
//------------------------------------------------------------------------------
int DragonTalon::GetCANID() const
{
	int id = -1;
	if ( m_talon != nullptr )
	{
		id = m_talon->GetDeviceID();
	}
	else
	{
//		printf( "DragonTalon::GetCANID: m_talon not initialized \n" );
	}
	return id;
}

// TODO: add doco
// Pass through methods to the TalonSRX
void DragonTalon::SetSensorPhase
(
	bool phaseSensor
)
{
	if ( m_talon != nullptr )
	{
		m_talon->SetSensorPhase( phaseSensor );
	}
	else
	{
//		printf( "DragonTalon::SetSensorPhase: m_talon not initialized \n" );
	}
}
void DragonTalon::SetInverted
(
	bool invert
)
{
	if ( m_talon != nullptr )
	{
		m_talon->SetInverted( invert );
	}
	else
	{
//		printf( "DragonTalon::SetInverted: m_talon not initialized \n" );
	}
}
bool DragonTalon::GetInverted() const
{
	bool isInverted = false;
	if ( m_talon != nullptr )
	{
		isInverted = m_talon->GetInverted();
	}
	else
	{
//		printf( "DragonTalon::SetInverted: m_talon not initialized \n" );
	}
	return isInverted;
}


//ErrorCode DragonTalon::ConfigSelectedFeedbackSensor
int DragonTalon::ConfigSelectedFeedbackSensor
(
	FeedbackDevice feedbackDevice,
	int pidIdx,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigSelectedFeedbackSensor( feedbackDevice, pidIdx, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigSelectedFeedbackSensor: m_talon not initialized \n" );
	}
	return error;
}

//ErrorCode DragonTalon::ConfigSelectedFeedbackSensor
int DragonTalon::ConfigSelectedFeedbackSensor
(
	RemoteFeedbackDevice feedbackDevice,
	int pidIdx,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigSelectedFeedbackSensor( feedbackDevice, pidIdx, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigSelectedFeedbackSensor: m_talon not initialized \n" );
	}
	return error;
}


//ErrorCode DragonTalon::ConfigPeakCurrentLimit
int DragonTalon::ConfigPeakCurrentLimit
(
	int amps,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigPeakCurrentLimit( amps, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigPeakCurrentLimit: m_talon not initialized \n" );
	}
	return error;
}


//ErrorCode DragonTalon::ConfigPeakCurrentDuration
int DragonTalon::ConfigPeakCurrentDuration
(
	int milliseconds,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigPeakCurrentDuration( milliseconds, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigPeakCurrentDuration: m_talon not initialized \n" );
	}
	return error;
}


//ErrorCode DragonTalon::ConfigContinuousCurrentLimit
int DragonTalon::ConfigContinuousCurrentLimit
(
	int amps,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigContinuousCurrentLimit( amps, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigContinuousCurrentLimit: m_talon not initialized \n" );
	}
	return error;
}


void DragonTalon::EnableCurrentLimit
(
	bool enable
)
{
	if ( m_talon != nullptr )
	{
		m_talon->EnableCurrentLimit( enable );
	}
	else
	{
//		printf( "DragonTalon::EnableCurrentLimit: m_talon not initialized \n" );
	}
}


void DragonTalon::SetNeutralMode
(
	NeutralMode neutralMode
)
{
	if ( m_talon != nullptr )
	{
		m_talon->SetNeutralMode( neutralMode );
	}
	else
	{
//		printf( "DragonTalon::SetNeutralMode: m_talon not initialized \n" );
	}
}


//------------------------------------------------------------------------------
// Method:		Reset
// Description:	Store the current encoder position, so GetEncoderPos will be
//				relative to this value.
// Returns:		void
//------------------------------------------------------------------------------
//void DragonTalon::Reset()
//{
//	SetEncPosition(0.0);
//}

void DragonTalon::Set
(
	double value 		// <I> - Updated target with the current control mode
)
{
	if ( m_talon != nullptr )
	{
	    double talonVal = value;
	    switch ( m_talon->GetControlMode() )
	    {
	        case ControlMode::Velocity:
	            talonVal = value * ( m_gearRatio * m_countsPerRev ) / 600.0;
	            break;

	        case ControlMode::Position:
	            talonVal = value * ( m_gearRatio * m_countsPerRev );
	            break;

	        default:
	            break;
	    }
		m_talon->Set( m_talon->GetControlMode(), talonVal );
	}
	else
	{
//		printf( "==>> DragonTalon::Set: m_talon not initialized \n " );
	}
}

//Note: for position, it takes rotations as target.
//For velocity, it takes desired RPM.
//Counts per rotation is set in chassis in accordance with constant in chassis map

void DragonTalon::SetControlMode
(
	TALON_CONTROL_MODE mode
)
{


	switch(mode)
	{
		case PERCENT:
			m_talon->Set( ControlMode::PercentOutput, 0.0 );
			break;

		case POSITION:
			m_talon->Set( ControlMode::Position, 0.0 );
			break;

		case VELOCITY:
			m_talon->Set( ControlMode::Velocity, 0.0 );
			break;

		case FOLLOWER:
			m_talon->Set( ControlMode::Follower, 0.0 );
			break;

		case MAGIC_MOTION:
			m_talon->Set( ControlMode::MotionMagic, 0.0 );
			break;

		default:
			m_talon->Set( ControlMode::PercentOutput, 0.0 );
			break;

	}

}


//------------------------------------------------------------------------------
// Method:		SelectClosedLoopProfile
// Description:	Selects which profile slot to use for closed-loop control
// Returns:		void
//------------------------------------------------------------------------------
void DragonTalon::SelectClosedLoopProfile
(
	int	   slot,			// <I> - profile slot to select
	int    pidIndex			// <I> - 0 for primary closed loop, 1 for cascaded closed-loop
)
{
	m_talon->SelectProfileSlot( slot, pidIndex );
}

void DragonTalon::SetClosedLoopParams
(
	int    slot,
	double kP,
	double kI,
	double kD,
	double kF,
	int	   timeOut
)
{
	// TODO: need to check parameters when I can get to GitHub
	m_talon->ConfigAllowableClosedloopError( slot, 0.0, 0.0 ); // always servo

	m_talon->Config_kP( slot, kP, 0.0 );  	//set p-gain
	m_talon->Config_kI( slot, kI, 0.0 );	//set i-gain
	m_talon->Config_kD( slot, kD, 0.0 );	//set d-gain
	m_talon->Config_kF( slot, kF, 0.0 );	//set feed-forward gain
}


float DragonTalon::GetRotationCount()
{
	int pos = m_talon->GetSelectedSensorPosition( 0 );
	float revs = pos / ( m_gearRatio * m_countsPerRev );
	return revs;
}

float DragonTalon::GetRPM()
{
	int vel = m_talon->GetSelectedSensorVelocity( 0 );
	float rpm = vel * ( 600.0 / ( m_gearRatio * m_countsPerRev ));
	return rpm;
}


void DragonTalon::SetAsSlave
(
    int         masterCANID         // <I> - master motor
)
{
    m_talon->Set( ControlMode::Follower, masterCANID );
}

void DragonTalon::ConfigMotionAcceleration
(
	float inchesPerSecondSquared
)
{
	float sensorUnitsPer100msPerSecond = inchesPerSecondSquared * 0.1; //Convert to 100ms
	sensorUnitsPer100msPerSecond /= (ChassisFactory::GetIChassis()->GetWheelDiameter() * M_PI); //Convert to rotations
	sensorUnitsPer100msPerSecond /= (m_gearRatio * m_countsPerRev); //Convert to counts (sensorUnits)

	m_talon->ConfigMotionAcceleration(sensorUnitsPer100msPerSecond, 0);
}

void DragonTalon::ConfigMotionCruiseVelocity
(
	float inchesPerSecond
)
{
	float sensorUnitsPer100ms = inchesPerSecond * 0.1; //Convert to 100ms
	sensorUnitsPer100ms /= (ChassisFactory::GetIChassis()->GetWheelDiameter() * M_PI); //Convert to rotations
	sensorUnitsPer100ms /= (m_gearRatio * m_countsPerRev); //Convert to counts (sensorUnits)
	m_talon->ConfigMotionCruiseVelocity(sensorUnitsPer100ms, 0);
}


