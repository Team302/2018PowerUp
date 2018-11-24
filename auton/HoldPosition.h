/*
 * HoldPosition.h
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

#ifndef SRC_AUTON_HOLDPOSITION_H_
#define SRC_AUTON_HOLDPOSITION_H_

#include <auton/PrimitiveParams.h>
#include <interfaces/IChassis.h>
#include <interfaces/IPrimitive.h>
#include <auton/GrabCube.h>
#include <auton/LiftElevator.h>

class HoldPosition : public IPrimitive {
public:
	void Init(PrimitiveParams*	params) override;
	void Run() override;
	bool IsDone() override;
	HoldPosition();
	virtual ~HoldPosition() = default;

private:
	const float kP = 10; //50, /75
	const float kI = 0.0;
	const float kD = 0.0;
	const float kF = 0.0;
	//Objects
	IChassis* m_chassis;
	LiftElevator* m_placeCube;
	GrabCube* m_grabCube;
	float m_timeRemaining; //In seconds
};

#endif /* SRC_AUTON_HOLDPOSITION_H_ */
