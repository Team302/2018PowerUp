/*
 * Lift.h
 *
 */

#ifndef SRC_SUBSYS_MECHANISMS_LIFT_H_
#define SRC_SUBSYS_MECHANISMS_LIFT_H_

#include <factories/MechanismFactory.h>
#include <interfaces/IMechanism.h>
#include <vector>

#include <subsys/components/DragonAnalogInput.h>
#include <subsys/components/DragonDigitalInput.h>
#include <subsys/components/DragonServo.h>
#include <subsys/components/DragonSolenoid.h>
#include <subsys/components/DragonTalon.h>
#include <subsys/mechanisms/Lift.h>

class Lift  : public IMechanism
{
public:

	enum LIFT_PRESET_HEIGHTS
	{
	    KEEP_SAME = -1,
		FLOOR,
		SWITCH,
		SCALE,
		SWITCH_HIGHER,
		MAX_VALUE
	};

	enum FOURBAR_CONTROL_MODE
	{
		POWER,
		UP_DOWN_STATE
	};

	Lift() = delete;
	Lift
	(
	        IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
	        const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
	        const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
	        const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
	        const DragonAnalogInputVector&      analogInputs,       // <I> - Analog Inputs
	        const DragonServoVector&            servos              // <I> - servos
	);

	virtual ~Lift() = default;

	// Setters
	void MoveElevatorMotor(float MoveElevatorMotor, bool safteySwitch);
	void MoveElevatorPreset( LIFT_PRESET_HEIGHTS preset);
	void SetElevatorRotationCount( float rotations );
	void SetFourbarPower(float power);
	void SetFourbarState(bool up);

	// Getters
	bool AtTarget();
	float GetElevatorRotationCount();
	float GetFourbarRotationCount();
	void ReleaseLatch();
	void SetClimbMode( bool enabled );
	void Periodic();

	IMechanism::MECHANISM_TYPE GetType() const override;

	// Height Array
//	float heightCounts[5] = { 1.45, 0, 1.82, 0 }; //Switch, ScaleL, ScaleDefault, ScaleH, TODO: Might add climb
	float heightCounts[5] = { 0.85, 0, 1.55, 0 }; //Switch, ScaleL, ScaleDefault, ScaleH, TODO: Might add climb

private:
	void MoveFourbar(bool up);
	void MoveFourbar(float speed, bool hold);
	void SetFourbarControlMode(FOURBAR_CONTROL_MODE controlMode);
	// Talons
	DragonTalon*			m_elevatorMotor;
	DragonTalon*			m_elevatorMotor2;

	DragonTalon*            m_fourbarMotor;

	// Solenoids
	DragonSolenoid*			m_fourbarSolenoid;

	float					m_targetHeight;
    float                   m_elevStartRotationCount;
    float                   m_fourbarStartRotationCount;

	bool					m_holding;
	bool					m_fourbarReleasingLatch;
	float 					m_fourbarReleaseTime;
	bool					m_fourbarCurrentPos;
	bool					m_fourbarPreviousPos;
	float					m_fourbarDownTime;
	float					m_fourbarUpTime;

	bool					m_elevClimbMode;
	FOURBAR_CONTROL_MODE	m_fourbarControlMode;

	float					m_kP;
	float					m_kI;
	float					m_kD;
	float					m_kF;

	const bool ELEVATOR_PERCENT_MODE = true;
	const float ELEVATOR_PERCENT_ACCEL_UP = 1.5; // per second
	const float ELEVATOR_PERCENT_ACCEL_DOWN = 5;
	const float ELEVATOR_MAX_PERCENT_UP = 1;
	const float ELEVATOR_MAX_PERCENT_DOWN = 1.00; //1.05 to counter act the constant upwards power
	const float ELEVATOR_STOP_THRESHOLD = 0.05;
	float m_currentElevatorSpeed;

	const float P_CONST = 0.1; //0.1
	const float ISDONE_ELEVATOR_THRESHOLD = 0.48;
	const float ELEVATOR_POWER_OFFSET = 0.05;

	const float FOURBAR_DOWN_ROTATIONS = -1.0; //-38
	const float FOURBAR_RELEASE_TIME = 0.1;
	const float FOURBAR_UP_TIME = 1.3; //seconds
	const float FOURBAR_DOWN_TIME = 1.8;
	const bool FOURBAR_TIME_MODE = true;
};

#endif /* SRC_SUBSYS_MECHANISMS_LIFT_H_ */
