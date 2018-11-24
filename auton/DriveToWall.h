/*
 * DriveToWall.h
 *
 *  Created on: Feb 20, 2018
 *      Author: jonah
 */

#ifndef SRC_AUTON_DRIVETOWALL_H_
#define SRC_AUTON_DRIVETOWALL_H_

#include <auton/PrimitiveParams.h>
#include <factories/ChassisFactory.h>
#include <auton/SuperDrive.h>
#include <interfaces/IChassis.h>
#include <interfaces/IPrimitive.h>
#include <auton/LiftElevator.h>
#include <auton/GrabCube.h>

class DriveToWall : public SuperDrive {
public:
	bool IsDone() override;
	void Init(PrimitiveParams* params) override;
	void Run() override;
	DriveToWall();
	virtual ~DriveToWall() = default;

private:
	LiftElevator* m_lift;
	GrabCube* m_grabCube;
	float m_minimumTime;
	float m_timeRemaining;
	int m_underSpeedCounts;
	const float SPEED_THRESHOLD = 3;
	const int UNDER_SPEED_COUNT_THRESHOLD = 2;

};

#endif /* SRC_AUTON_DRIVETOWALL_H_ */
