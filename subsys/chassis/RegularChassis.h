/*
 * RegularChassis.h
 *
 *  Created on: Dec 20, 2017
 *      Author: jonah
 */

#ifndef SRC_SUBSYS_REGULAR_REGULARCHASSIS_H_
#define SRC_SUBSYS_REGULAR_REGULARCHASSIS_H_

//Includes
#include <vector>
#include <ctre/phoenix/Sensors/PigeonIMU.h>
//Team302 includes
#include <interfaces/IChassis.h>
#include <subsys/components/DragonTalon.h>
#include <subsys/components/DragonNavX.h>
#include <subsys/components/DragonPigeon.h>
#include <utils/DragonMath.h>

class RegularChassis: public IChassis {
public:
	//Units can be found in the IChassis interface (im lazy)

	//Getters
	//Robot Constants getters
	double GetWheelDiameter() const override;

	double GetLeftMasterMotorRotationCount() const override;
	double GetRightMasterMotorRotationCount() const override;
	double GetVelocity() const override;
	double GetXVelocity() const override;
	double GetYVelocity() const override;
	double GetDistance() const override; //Returns distance in inches
	double GetXLocation() const override;
	double GetYLocation() const override;
	double GetHeading() const override;
	double GetTargetHeading() const override;
	bool CanStrafe() const override;

	//Setters
	void EnableBrakeMode(bool enabled) override;
	void SetTalonMode(DragonTalon::TALON_CONTROL_MODE mode) override;
	void SetVelocityParams(float kP, float kI, float kD, float kF, float leftSpeed, float rightSpeed) override;
	void SetPIDParams(float kP, float kI, float kD, float kF) override;
	void SetDriveMagnitudes(double xPower, double yPower, double rotationPower) override;
	void SetLeftRightMagnitudes(double leftPower, double rightPower) override;
	void UpdateChassis() override;
	void EnableCurrentLimiting(bool enabled) override;

	void SetTargetHeading(double heading) override;
	void PrintDebug() override;
	void ResetChassis() override;
	void ResetGyro() override;

	RegularChassis
	(
		float 						wheelDiameter,		// <I> - Diameter of the wheel
	    float 						wheelBase,			// <I> - Front-Back distance between wheel centers
		float 						track,				// <I> - Left-Right distance between wheels (same axle)
		std::vector<DragonTalon*> 	motorControllers	// <I> - Motor Controllers
	);
	RegularChassis() = delete;
	virtual ~RegularChassis();

private:
	double GetLeftVelocity() const;
	double GetRightVelocity() const;
	double GetBestOfTwo(double x1, double x2) const; //Returns the value the furthest distance from zero

	DragonNavX* m_navx;
    DragonPigeon* m_pigeon;

	DragonTalon* m_frontLeftMotor;
	DragonTalon* m_frontRightMotor;
	DragonTalon* m_backLeftMotor;
	DragonTalon* m_backRightMotor;

	Point2D m_location;

	double m_resetHeading;
	double m_targetHeading;

	//These variables are for finding left and right delta distance
	double m_pDistance;

	double m_pathTravelVelocityTarget;

	float m_wheelDiameter;	//Wheel diameter in inches
	float m_wheelBase;		//Front back distance between wheel centers
	float m_track;			//Left right distance between wheel centers

	float velocityToRPM; 	//This is a var that is calculated in the constructor and is never changed (can we make this const some how?)
							//Also, this is used when setting velocities when in velocity movement mode

	mutable bool m_periodicMSGWritten;

};

#endif /* SRC_SUBSYS_REGULAR_REGULARCHASSIS_H_ */
