/*
 * PlaceCube.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Austin
 */

#ifndef SRC_AUTON_LIFTELEVATOR_H_
#define SRC_AUTON_LIFTELEVATOR_H_

// auton includes
#include <auton/PrimitiveParams.h>
#include <factories/MechanismFactory.h>
#include <interfaces/IMechanism.h>
#include <interfaces/IPrimitive.h>
// mech includes
#include <subsys/mechanisms/Lift.h>
#include <auton/GrabCube.h>

class LiftElevator : public IPrimitive {
public:
	void Init( PrimitiveParams* params ) override;
	void Run() override;
	bool IsDone() override;

	LiftElevator();
	virtual ~LiftElevator() = default;

private:
	// Mechs
	Lift* m_lift;
	PrimitiveParams* m_params;
	// Prim Params
	Lift::LIFT_PRESET_HEIGHTS m_deliverHeight;
	bool m_grabberInit;
};

#endif /* SRC_AUTON_LIFTELEVATOR_H_ */
