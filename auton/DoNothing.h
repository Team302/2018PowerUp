/*
 * DoNothing.h
 *
 *  Created on: Jan 18, 2018
 *      Author: jonah (the cool guy)
 */

#ifndef SRC_AUTON_DONOTHING_H_
#define SRC_AUTON_DONOTHING_H_

//Team302 includes
#include <auton/PrimitiveParams.h>
#include <interfaces/IChassis.h>
#include <interfaces/IPrimitive.h>
#include <auton/LiftElevator.h>
#include <auton/GrabCube.h>

class DoNothing : public IPrimitive {
public:
	DoNothing();
	virtual ~DoNothing() = default;
	void Init(PrimitiveParams* params) override;
	void Run() override;
	bool IsDone() override;

private:
	float m_maxTime;		//Target time
	float m_currentTime;	//Time since init
	IChassis* m_chassis;	//chassis
	LiftElevator* m_lift;
	GrabCube* m_grabCube;
};

#endif /* SRC_AUTON_DONOTHING_H_ */
