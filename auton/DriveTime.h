/*
 * DriveTime.h
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

#ifndef SRC_AUTON_DRIVETIME_H_
#define SRC_AUTON_DRIVETIME_H_

//Includes
//Team302 includes
#include <auton/SuperDrive.h>
#include <auton/DriveTime.h>
#include <interfaces/IChassis.h>
#include <interfaces/IPrimitive.h>
#include <auton/LiftElevator.h>
#include <auton/GrabCube.h>

class DriveTime: public SuperDrive {
public:
	DriveTime();
	virtual ~DriveTime() = default;
	void Init(PrimitiveParams* params) override;
	void Run() override;
	bool IsDone() override;

private:
	LiftElevator* m_lift;
	GrabCube* m_grabCube;
	float m_timeRemaining;          //In seconds

};

#endif /* SRC_AUTON_DRIVETIME_H_ */
