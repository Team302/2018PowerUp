/*
 * Lift.cpp
 *
 */
#include <factories/MechanismFactory.h>
#include <subsys/mechanisms/Lift.h>
#include <interfaces/IPrimitive.h>

#include <interfaces/IMechanism.h>
#include <vector>

#include <subsys/components/DragonAnalogInput.h>
#include <subsys/components/DragonDigitalInput.h>
#include <subsys/components/DragonServo.h>
#include <subsys/components/DragonSolenoid.h>
#include <subsys/components/DragonTalon.h>
#include <iostream>

#include <SmartDashboard/SmartDashboard.h>

#include <thirdParty/puxixml/pugixml.hpp>

Lift::Lift(IMechanism::MECHANISM_TYPE type,               // <I> - manipulator Type
		const DragonTalonVector& motorControllers,   // <I> - Motor Controllers
		const DragonSolenoidVector& solenoids,          // <I> - Solenoids
		const DragonDigitalInputVector& digitalInputs,      // <I> - Digital Inputs
		const DragonAnalogInputVector& analogInputs,       // <I> - Analog Inputs
		const DragonServoVector& servos              // <I> - servos
		) :
		m_elevatorMotor(nullptr), m_elevatorMotor2(nullptr), m_fourbarMotor(nullptr), m_fourbarSolenoid(nullptr), m_targetHeight(0.0), m_elevStartRotationCount(0.0), m_fourbarStartRotationCount(0.0), m_holding(false), m_fourbarReleasingLatch(false), m_fourbarReleaseTime(-1.0), m_fourbarCurrentPos(true), m_fourbarPreviousPos(true), m_fourbarDownTime(-1.0), m_fourbarUpTime(-1.0), m_elevClimbMode(false), m_fourbarControlMode(POWER), m_kP(P_CONST), m_kI(0.0), m_kD(0.0), m_kF(0.0), m_currentElevatorSpeed(0.0)

{
//	printf("Lift constructed\n");
	for (unsigned int inx = 0; inx < motorControllers.size(); ++inx)
	{
//		printf("==> motor controller [ %d ] = %d \n", inx, motorControllers[inx]->GetType());
		switch (motorControllers[inx]->GetType())
		{
		case DragonTalon::TALON_TYPE::ELEVATOR_MASTER:
			m_elevatorMotor = motorControllers[inx];
			m_elevStartRotationCount = m_elevatorMotor->GetRotationCount();
			break;

		case DragonTalon::TALON_TYPE::ELEVATOR_SLAVE:
			m_elevatorMotor2 = motorControllers[inx];
			break;

		case DragonTalon::TALON_TYPE::FOURBAR_LIFT_MOTOR:
			m_fourbarMotor = motorControllers[inx];
			m_fourbarStartRotationCount = m_fourbarMotor->GetRotationCount();
//			frc::SmartDashboard::PutNumber("fourbar start rot", m_fourbarStartRotationCount);
			break;

		default:
			printf("==>> Lift: Invalid Motor %d \n", motorControllers[inx]->GetType());
			break;
		}
	}

//	for (unsigned int inx = 0; inx < digitalInputs.size(); ++inx)
//	{
////		printf("==> digital input [ %d ] = %d \n", inx, digitalInputs[inx]->GetType());
//		switch (digitalInputs[inx]->GetType())
//		{
//		case DragonDigitalInput::ELEVATOR_FLOOR:
//			m_lmtFloor = digitalInputs[inx];
//			break;
//
//		case DragonDigitalInput::ELEVATOR_SWITCH:
//			m_lmtSwitch = digitalInputs[inx];
//			break;
//
//		case DragonDigitalInput::ELEVATOR_SCALE:
//			m_lmtScale = digitalInputs[inx];
//			break;
//
//		case DragonDigitalInput::ELEVATOR_MAX:
//			m_lmtMax = digitalInputs[inx];
//			break;
//
//		default:
//			printf("==>> Lift: Invalid Digital Input %d \n", digitalInputs[inx]->GetType());
//			break;
//
//		}
//	}

	for (unsigned int inx = 0; inx < solenoids.size(); ++inx)
	{
//		printf("==> solenoids [ %d ] = %d \n", inx, solenoids[inx]->GetType());
		switch (solenoids[inx]->GetType())
		{
		case DragonSolenoid::CONTROL_4BAR:
			m_fourbarSolenoid = solenoids[inx];
			break;

		default:
			printf("==>> Lift: Invalid solenoid %d \n", solenoids[inx]->GetType());
			break;

		}
	}
//	SmartDashboard::PutNumber("Elevator Start Rotation Counts: ", m_elevStartRotationCount);
	SmartDashboard::PutNumber("4Bar Start Rotation Counts: ", m_fourbarStartRotationCount);
}

IMechanism::MECHANISM_TYPE Lift::GetType() const
{
	return IMechanism::LIFT;
}

void Lift::MoveElevatorMotor(float moveElevatorMotor, bool safetySwitch) //TODO: Pass another variable to disable elevator height limiting.
{
	m_elevatorMotor->SetControlMode(DragonTalon::PERCENT);
	if (m_elevClimbMode)
	{
		frc::SmartDashboard::PutBoolean("in climb mode", true);
		m_elevatorMotor->SetNeutralMode(NeutralMode::Coast); //Set elevator to coast when climbing
		m_elevatorMotor2->SetNeutralMode(NeutralMode::Coast);
	}
	else
	{
		frc::SmartDashboard::PutBoolean("in climb mode", false);
		m_elevatorMotor->SetNeutralMode(NeutralMode::Brake); //We need this on brake mode otherwise
		m_elevatorMotor2->SetNeutralMode(NeutralMode::Brake);
	}

//	if (m_lmtMax != nullptr)
//	{
////		frc::SmartDashboard::PutBoolean("max height prox", m_lmtMax->Get());
//		frc::SmartDashboard::PutBoolean("max prox not null", true);
////		if (!m_lmtMax->Get()) //we can keep going up, give full control
//		if (true) //uncomment line above to use prox
//		{
//			if (m_elevClimbMode)
//			{
//				m_elevatorMotor->Set(moveElevatorMotor);
//			}
//			else
//			{
//				m_elevatorMotor->Set(moveElevatorMotor + ELEVATOR_POWER_OFFSET); //TODO: move 0.1 to a constant
//			}
//		}
//		else //we cannot go up anymore, allow control if going downwards
//		{
//			if (moveElevatorMotor < 0)
//			{
//				if (m_elevClimbMode)
//				{
//					m_elevatorMotor->Set(moveElevatorMotor);
//				}
//				else
//				{
//					m_elevatorMotor->Set(moveElevatorMotor + ELEVATOR_POWER_OFFSET); //TODO: move 0.1 to a constant
//				}
//			}
//			else
//			{
//				if (m_elevClimbMode)
//				{
//					m_elevatorMotor->Set(0);
//				}
//				else
//				{
//					m_elevatorMotor->Set(ELEVATOR_POWER_OFFSET); //TODO: move 0.1 to a constant
//				}
//			}
//		}
//	}
//	else //there is not prox sensor, allow full control
//	{
		frc::SmartDashboard::PutBoolean("max prox not null", false);
		if (m_elevClimbMode)
		{
			m_elevatorMotor->Set(moveElevatorMotor);
		}
		else
		{
			m_elevatorMotor->Set(moveElevatorMotor + ELEVATOR_POWER_OFFSET); //TODO: move 0.1 to a constant
		}
//	}
	frc::SmartDashboard::PutNumber("elev rots relative", GetElevatorRotationCount());
}

void Lift::MoveElevatorPreset(Lift::LIFT_PRESET_HEIGHTS height)
{
	bool dontChange = false;

	// Find target height encoder revolutions
	switch (height)
	{
	case Lift::FLOOR:
		SetFourbarState(false);
		m_targetHeight = 0.0;
		break;

	case Lift::SWITCH:
		SetFourbarState(true);
		m_targetHeight = 0.0; //Lift::heightCounts[0]
		break;

	case Lift::SCALE:
		SetFourbarState(true);
		m_targetHeight = Lift::heightCounts[2];
		break;

	case Lift::SWITCH_HIGHER:
		SetFourbarState(false);
		m_targetHeight = Lift::heightCounts[0];
		break;

	case Lift::KEEP_SAME:
		dontChange = true;
		break;

	default:
		printf("Invalid height specified %d \n", height);
	}

	if (!dontChange)
	{
		if (!ELEVATOR_PERCENT_MODE) //only set position mode when we
		{
			m_elevatorMotor->SetControlMode(DragonTalon::POSITION);
			// Run motor to target location Digital Input not
			m_elevatorMotor->SetClosedLoopParams(0, P_CONST, m_kI, m_kD, m_kF, 0);
			SetElevatorRotationCount(m_targetHeight);
		}
	}
}

//true is up!
void Lift::MoveFourbar(bool up)
{
	m_fourbarCurrentPos = up;
	if (m_fourbarPreviousPos && !m_fourbarCurrentPos) //switch to going down
	{
		m_fourbarDownTime = FOURBAR_DOWN_TIME;
		m_fourbarUpTime = -1;
	}
	else if (!m_fourbarPreviousPos && m_fourbarCurrentPos) //switch to going up
	{
		m_fourbarDownTime = -1;
		m_fourbarUpTime = FOURBAR_UP_TIME;
	}
	m_fourbarPreviousPos = m_fourbarCurrentPos; //update previous value to current value

//	if (m_fourbarMotor != nullptr && !m_fourbarReleasingLatch)
//	{
//		//down is -39, AKA FOURBAR_DOWN_ROTATIONS
//		//up is 0. greater than 0 is breaking the robot because we are going to high
//		if (up)
//		{
//			if (GetFourbarRotationCount() < 0)
//			{
//				MoveFourbar(0.65f, true);
//			}
//			else
//			{
//				MoveFourbar(0.0f, true);
//			}
//		}
//		else
//		{
//			if (GetFourbarRotationCount() > FOURBAR_DOWN_ROTATIONS)
//			{
//				MoveFourbar(-0.45f, true);
//			}
//			else
//			{
//				MoveFourbar(0.0f, false);
//			}
//		}
//	}
}

void Lift::MoveFourbar(float speed, bool hold)
{
	if (m_fourbarMotor != nullptr && !m_fourbarReleasingLatch)
	{
		frc::SmartDashboard::PutNumber("fourbar relative rotations", GetFourbarRotationCount());
		if (hold)
		{
			m_fourbarMotor->Set(speed + 0.06);
		}
		else
		{
			m_fourbarMotor->Set(speed);
		}
	}
}

bool Lift::AtTarget()
{
//	frc::SmartDashboard::PutNumber("elevator progress: ", m_targetHeight - GetElevatorRotationCount());
//	frc::SmartDashboard::PutNumber("target height auton: ", m_targetHeight);
//	frc::SmartDashboard::PutNumber("elevator rotaiotn count auton:", GetElevatorRotationCount());
	return (m_targetHeight - GetElevatorRotationCount()) < ISDONE_ELEVATOR_THRESHOLD;
}

void Lift::SetElevatorRotationCount(float rotations)
{
	m_elevatorMotor->Set(rotations + m_elevStartRotationCount);
}

float Lift::GetElevatorRotationCount()
{
	return m_elevatorMotor->GetRotationCount() - m_elevStartRotationCount; // TODO: Check to make sure this is accurate, use this for motion magic.
}

float Lift::GetFourbarRotationCount()
{
	frc::SmartDashboard::PutNumber("raw fourbar encoder", m_fourbarMotor->GetRotationCount());
	return m_fourbarMotor->GetRotationCount() - m_fourbarStartRotationCount;
}

void Lift::SetFourbarPower(float power)
{
	SetFourbarControlMode(POWER);
	frc::SmartDashboard::PutString("Fourbar mode:", "POWER");
	MoveFourbar(power, true);
	frc::SmartDashboard::PutNumber("fourbar relative rots", GetFourbarRotationCount());
}

void Lift::SetFourbarState(bool up)
{
	SetFourbarControlMode(UP_DOWN_STATE);
	frc::SmartDashboard::PutString("Fourbar mode:", "UP_DOWN_STATE");
	MoveFourbar(up);
}

void Lift::ReleaseLatch()
{
	m_fourbarReleaseTime = 0.1;
}

void Lift::SetClimbMode(bool enabled)
{
	m_elevClimbMode = enabled;
}

void Lift::SetFourbarControlMode(FOURBAR_CONTROL_MODE controlMode)
{
	m_fourbarControlMode = controlMode;
}

void Lift::Periodic()
{
	if (m_fourbarReleaseTime >= 0) //just to prevent this from happening all the time
	{
		m_fourbarReleaseTime -= 0.020; //constant broke for some reason
		m_fourbarMotor->SetControlMode(DragonTalon::PERCENT);
		m_fourbarMotor->Set(0.8);
		m_fourbarReleasingLatch = true;
//		frc::SmartDashboard::PutNumber("fourbar release time", m_fourbarReleaseTime);
//		frc::SmartDashboard::PutString("fourbar is doing this: ", "releasing latch");
	}
	else
	{
		m_fourbarReleasingLatch = false;

		//Run periodic stuff for elevator and fourbar
		switch (m_fourbarControlMode)
		{
		case POWER:
			break;

		case UP_DOWN_STATE:
			if (m_fourbarMotor != nullptr && !m_fourbarReleasingLatch)
			{
				if (FOURBAR_TIME_MODE)
				{
					if (m_fourbarUpTime > 0) //move up
					{
						m_fourbarUpTime -= 0.020;
						MoveFourbar(0.65f, true);
//							printf("Fourbar going UP\n");
					}
					else if (m_fourbarDownTime > 0) //move down
					{
						m_fourbarDownTime -= 0.020;
						MoveFourbar(-0.45f, true);
//							printf("Fourbar going DOWN\n");
					}
					else //hold, or stay down
					{
						if (m_fourbarCurrentPos) //hold
						{
							MoveFourbar(0.0f, true);
//								printf("Fourbar HOLDING\n");
						}
						else  //stay down
						{
							MoveFourbar(0.0f, false);
//								printf("Fourbar STAYING DOWN\n");
						}

					}
//						printf("up time rem %g", m_fourbarUpTime);
//						printf(" down time rem %g\n", m_fourbarDownTime);
				}
				else
				{
					//down is -39, AKA FOURBAR_DOWN_ROTATIONS
					//up is 0. greater than 0 is breaking the robot because we are going to high
					if (m_fourbarCurrentPos)
					{
						if (GetFourbarRotationCount() < 0)
						{
							MoveFourbar(0.65f, true);
//							frc::SmartDashboard::PutString("fourbar is doing this: ", "raising");
						}
						else
						{
							MoveFourbar(0.0f, true);
//							frc::SmartDashboard::PutString("fourbar is doing this: ", "raised");
						}
					}
					else
					{
						if (GetFourbarRotationCount() > FOURBAR_DOWN_ROTATIONS)
						{
							MoveFourbar(-0.45f, true);
//							frc::SmartDashboard::PutString("fourbar is doing this: ", "lowering");
						}
						else
						{
							MoveFourbar(0.0f, false);
//							frc::SmartDashboard::PutString("fourbar is doing this: ", "lowered");
						}
					}
				}

			}
			break;

		default:
			break;
		}
	}
	frc::SmartDashboard::PutNumber("fourbar relative rots", GetFourbarRotationCount());

	//run elevator periodic stuff
	if (ELEVATOR_PERCENT_MODE)
	{
		if (std::abs(m_targetHeight - GetElevatorRotationCount()) > ELEVATOR_STOP_THRESHOLD) //THRESHOlD
		{
			if (GetElevatorRotationCount() < m_targetHeight) //going up
			{
				if (m_currentElevatorSpeed >= 0) //current velocity is positive (matching desired sign)
				{
					if (m_currentElevatorSpeed < ELEVATOR_MAX_PERCENT_UP) //we have not reached max speed, we can accelerate more
					{
						m_currentElevatorSpeed += ELEVATOR_PERCENT_ACCEL_UP * 0.02;
					}
					else 												//we have reached max speed
					{
						m_currentElevatorSpeed = ELEVATOR_MAX_PERCENT_UP;
					}
				}
				else //current velocity is NOT positive, make the current speed in the correct direction
				{
					m_currentElevatorSpeed = ELEVATOR_PERCENT_ACCEL_UP * 0.02; //make it positive
				}
			}
			else //going down
			{
				if (m_currentElevatorSpeed < 0) // current velocity is negative (matching desired sign)
				{
					if (-m_currentElevatorSpeed < ELEVATOR_MAX_PERCENT_DOWN) // we have not reached max speed, keep accelerating
					{
						m_currentElevatorSpeed -= ELEVATOR_PERCENT_ACCEL_DOWN * 0.02;
					}
					else												// we've reached max speed
					{
						m_currentElevatorSpeed = -ELEVATOR_MAX_PERCENT_DOWN;
					}
				}
				else							// current velocity is positive, incorrect sign
				{
					m_currentElevatorSpeed = -ELEVATOR_PERCENT_ACCEL_DOWN * 0.02; //make it negative
				}
			}
		}
		else
		{
			//Set the current power to the hold power
			m_currentElevatorSpeed = ELEVATOR_POWER_OFFSET;
		}
		m_elevatorMotor->SetControlMode(DragonTalon::PERCENT);
		m_elevatorMotor->Set(m_currentElevatorSpeed);
	}

}
