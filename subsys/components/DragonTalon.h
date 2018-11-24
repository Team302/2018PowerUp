/*
 * DragonTalon.h
 *
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONTALON_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONTALON_H_

#include <string>
#include <vector>

#include <ctre/phoenix/ErrorCode.h>
#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>

using namespace  ctre::phoenix;
using namespace  ctre::phoenix::motorcontrol;
using namespace  ctre::phoenix::motorcontrol::can;

class DragonTalon
{
	public:

		enum TALON_TYPE
		{
			UNKNOWN_TALON_TYPE = -1,
			MECANUM_FRONT_LEFT,
			MECANUM_FRONT_LEFT2,
			MECANUM_FRONT_RIGHT,
			MECANUM_FRONT_RIGHT2,
			MECANUM_BACK_LEFT,
			MECANUM_BACK_LEFT2,
			MECANUM_BACK_RIGHT,
			MECANUM_BACK_RIGHT2,
			TANK_LEFT_MASTER,
			TANK_LEFT_SLAVE1,
			TANK_LEFT_SLAVE2,
			TANK_RIGHT_MASTER,
			TANK_RIGHT_SLAVE1,
			TANK_RIGHT_SLAVE2,
			CLIMBER_MASTER,
			ELEVATOR_MASTER,
			ELEVATOR_SLAVE,
			SIDE_HANGER_MOTOR,
			ACTIVE_INTAKE_WHEELS,
			FOURBAR_LIFT_MOTOR,
			ACTIVE_INTAKE_SLAVE,
			MAX_TALON_TYPES
		};

		enum TALON_SENSOR_TYPE
		{
			NO_SENSOR = -1,
			QUAD_ENCODER,
			UNKNOWN_SENSOR,
			ANALOG_POT,
			ANALOG_ENCODER,
			ENCODER_RISING,
			ENCODER_FALLING,
			CTRE_MAG_ENCODER_RELATIVE,
			CTRE_MAG_ENCODER_ABSOLUTE,
			PULSE_WIDTH,
			MAX_SENSOR_TYPES
		};

		enum TALON_CONTROL_MODE
		{
			PERCENT,
			POSITION,
			VELOCITY,
			FOLLOWER,
			MAGIC_MOTION,
			MAX_TALON_MODES
		};

		//------------------------------------------------------------------------------
		// Method:		<<constructor>>
		// Description:	Since we have methods on the CANTalon that don't appear to be
		// 				working, we have
		//------------------------------------------------------------------------------
		DragonTalon
		(
			DragonTalon::TALON_TYPE	deviceType,		// <I> - Usage of the motor
			int 					deviceID,		// <I> - CAN ID
			int						countsPerRev,   // <I> - counts per revolution for the encoder
			float					gearRatio		// <I> - gear ratio for encoder to output shaft
		);


		//------------------------------------------------------------------------------
		// Method:		Reset
		// Description:	Store the current encoder position, so GetEncoderPos will be
		//				relative to this value.
		// Returns:		void
		//------------------------------------------------------------------------------
//		void Reset() override;

        void Set //when in velocity, its RPM
        (
            double value            // <I> - Updated target with the current control mode
        );

		//------------------------------------------------------------------------------
		// Method:		SetControlMode
		// Description:	Switch the control mode for the talon
		//
		//				Note: Changing the mode changes the units for the target:
		//						position - rotations is the target.
		//						velocity - RPM is the target.
		//Counts per rotation is set in chassis in accordance with constant in chassis map
		// Returns:		void
		//------------------------------------------------------------------------------
		void SetControlMode
		(
			TALON_CONTROL_MODE mode		// <I> - talon control mode
		);


		//------------------------------------------------------------------------------
		// Method:		SelectClosedLoopProfile
		// Description:	Selects which profile slot to use for closed-loop control
		// Returns:		void
		//------------------------------------------------------------------------------
		void SelectClosedLoopProfile
		(
			int	   slot,			// <I> - profile slot to select
			int    pidIndex			// <I> - 0 for primary closed loop, 1 for cascaded closed-loop
		);

		//------------------------------------------------------------------------------
		// Method:		SetClosedLoopParams
		// Description:	Set the closed loop control parameters (PIDF coefficients)
		// Returns:		void
		//------------------------------------------------------------------------------
		void SetClosedLoopParams
		(
			int	   slot,				// <I> - profile slot to set
			double kP,					// <I> - proportional coefficient
			double kI,					// <I> - integral coefficient
			double kD,					// <I> - derivative coefficient
			double kF,					// <I> - feed-forward coefficient
			int	   timeOut				// <I> - timeout in ms
		);

		//------------------------------------------------------------------------------
		// Method:		<<destructor>>
		// Description:	clean up
		//------------------------------------------------------------------------------
		virtual ~DragonTalon() = default;

		//------------------------------------------------------------------------------
		// Method:		GetType
		// Description:	Return the talon's usage type
		// Returns:		DragonTalon::TALON_TYPE			talon's type
		//------------------------------------------------------------------------------
		DragonTalon::TALON_TYPE GetType() const;

		//------------------------------------------------------------------------------
		// Method:		GetCANID
		// Description:	Return the talon's CAN ID
		// Returns:		int			talon's CAN ID
		//------------------------------------------------------------------------------
		int GetCANID() const;

		// TODO: add doco
		// Pass through methods to the TalonSRX
		void SetSensorPhase
		(
			bool PhaseSensor
		);

		void SetInverted
		(
			bool invert
		);
		bool GetInverted() const;

//		ErrorCode ConfigSelectedFeedbackSensor
		int ConfigSelectedFeedbackSensor
		(
			FeedbackDevice feedbackDevice,
			int pidIdx,
			int timeoutMs
		);

//		ErrorCode ConfigSelectedFeedbackSensor
		int ConfigSelectedFeedbackSensor
		(
			RemoteFeedbackDevice feedbackDevice,
			int pidIdx,
			int timeoutMs
		);

//		ErrorCode ConfigPeakCurrentLimit
		int ConfigPeakCurrentLimit
		(
			int amps,
			int timeoutMs
		);

//		ErrorCode ConfigPeakCurrentDuration
		int ConfigPeakCurrentDuration
		(
			int milliseconds,
			int timeoutMs
		);

//		ErrorCode ConfigContinuousCurrentLimit
		int ConfigContinuousCurrentLimit
		(
			int amps,
			int timeoutMs
		);

		void EnableCurrentLimit
		(
			bool enable
		);

		void SetNeutralMode
		(
			NeutralMode neutralMode
		);

		//Encoder getters
		float GetRotationCount();
		float GetRPM();

		void SetAsSlave
		(
		    int         masterCANID         // <I> - master motor
		);

		//Methods for Motion Magic control mode
		void ConfigMotionAcceleration
		(
			float inchesPerSecondSquared
		);

		void ConfigMotionCruiseVelocity
		(
			float inchesPerSecond
		);

	private:
		TalonSRX*				m_talon;
		DragonTalon::TALON_TYPE	m_type;							// Talon usage type
		int						m_zeroPos;						// Position when encoder was reset
		bool					m_sensorInverted;				// sensor is inverted
		int						m_countsPerRev;
		float					m_gearRatio;
};

typedef std::vector<DragonTalon*> DragonTalonVector;


#endif /* SRC_SUBSYS_COMPONENTS_DRAGONTALON_H_ */
