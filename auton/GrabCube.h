/*
 * GrabCube.h
 *
 *  Created on: Jan 26, 2018
 *      Author: Austin
 */

#ifndef SRC_AUTON_GRABCUBE_H_
#define SRC_AUTON_GRABCUBE_H_

#include <auton/PrimitiveParams.h>
#include <factories/MechanismFactory.h>
#include <interfaces/IMechanism.h>
#include <interfaces/IPrimitive.h>
#include <subsys/mechanisms/Grabber.h>
#include <subsys/mechanisms/ActiveGrabber.h>

class GrabCube : public IPrimitive {
public:
	void Init(PrimitiveParams* params) override;
	void Run() override;
	bool IsDone() override;

	GrabCube();
	virtual ~GrabCube() = default;

private:
	// Grabber instance
	ActiveGrabber* m_grabber;
	PrimitiveParams* m_params;
	bool m_ran;
};

#endif /* SRC_AUTON_GRABCUBE_H_ */
