/*
 * IChassis.h
 *
 *  Created on: Oct 5, 2017
 *      Author: jonah
 */

#ifndef SRC_INTERFACES_ICHASSIS_H_
#define SRC_INTERFACES_ICHASSIS_H_

#include <subsys/components/DragonTalon.h>
//#include <subsys/factories/ChassisFactory.h>

class IChassis {
public:
	//Getters
	//Robot Constants
	virtual double GetWheelDiameter() const = 0;

	virtual double GetLeftMasterMotorRotationCount() const = 0;
	virtual double GetRightMasterMotorRotationCount() const = 0;
	virtual double GetVelocity() const = 0; //Magnitude of both velocities
	virtual double GetXVelocity() const = 0;
	virtual double GetYVelocity() const = 0;
	virtual double GetDistance() const = 0; //Returns total distance traveled in inches. Averages left and right
	virtual double GetXLocation() const = 0;
	virtual double GetYLocation() const = 0;
	virtual double GetHeading() const = 0; //In degrees, + is clockwise
	virtual double GetTargetHeading() const = 0;
	virtual bool CanStrafe() const = 0; //Does this chassis have powered strafing? Mecanum=true, Omni=false

	//Methods for power drive mode
	virtual void EnableBrakeMode(bool enabled) = 0;
	virtual void SetTalonMode(DragonTalon::TALON_CONTROL_MODE mode) = 0;
	virtual void SetVelocityParams(float kP, float kI, float kD, float kF, float leftSpeed, float rightSpeed) = 0;
	virtual void SetPIDParams(float kP, float kI, float kD, float kF) = 0;
	virtual void SetDriveMagnitudes(double xPower, double yPower, double rotationPower) = 0; // from -1 to 1. used in teleop drive
	virtual void SetLeftRightMagnitudes(double leftPower, double rightPower) = 0;
	virtual void EnableCurrentLimiting(bool enabled) = 0;

	virtual void SetTargetHeading(double heading) = 0;
	virtual void UpdateChassis() = 0; //This applies all motor speeds/power/velocity to the cantalons and updates the x, y direction calculations
	virtual void ResetChassis() = 0; //This resets the x and y and robot distance stuff
	virtual void ResetGyro() = 0;

	virtual void PrintDebug() = 0; // SmartDashboard stuff

	//TODO: add getters for max velocity (strafe velocity will be different) to be used in automatic controller calibration

	IChassis() = default;
	virtual ~IChassis() = default;
};


#endif /* SRC_INTERFACES_ICHASSIS_H_ */
