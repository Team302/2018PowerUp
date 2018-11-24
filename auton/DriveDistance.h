/*
 * DriveDistance.h
 *
 *  Created on: Jan 18, 2018
 *      Author: jonah
 */

#ifndef SRC_AUTON_DRIVEDISTANCE_H_
#define SRC_AUTON_DRIVEDISTANCE_H_

#include <auton/PrimitiveParams.h>
#include <factories/ChassisFactory.h>
#include <auton/SuperDrive.h>
#include <interfaces/IChassis.h>
#include <interfaces/IPrimitive.h>
#include <auton/LiftElevator.h>
#include <auton/GrabCube.h>

class DriveDistance : public SuperDrive {
public:
	bool IsDone() override;
	void Init(PrimitiveParams* params) override;
	void Run() override;
	DriveDistance();
	virtual ~DriveDistance() = default;

protected:
    void SetDistance
    (
        double distance
    );
private:
	void CalculateSlowDownDistance();
	//TODO: remove timeout. it is no longer being used
//	const float TIMEOUT_MULTIPIER = 200000; // Multiplier for the max expected time (speed * distance) * TIMEOUT_MULTIPLIER = expected time
									//1.4
	PrimitiveParams* m_params;
	LiftElevator* m_lift;
	GrabCube* m_grabCube;

	float m_targetDistance;
	float m_initialDistance;
	float m_timeRemaining;

	float m_minSpeedCountTime;
	int m_underSpeedCounts;
	float m_startHeading;
	float m_endHeading;
	float m_minSpeed;
	bool m_arcing;

	const float SPEED_THRESHOLD = 1.5;
	const float MIN_SPEED_COUNT_TIME = 0.5; //seconds before we start checking for wall collisions
	const int UNDER_SPEED_COUNT_THRESHOLD = 4;
	const float DECEL_TIME_MULTIPLIER = 0.85; //0.75
};

#endif /* SRC_AUTON_DRIVEDISTANCE_H_ */
