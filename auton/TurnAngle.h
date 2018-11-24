/*
 * TurnAngle.h
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

#ifndef SRC_AUTON_TURNANGLE_H_
#define SRC_AUTON_TURNANGLE_H_

//includes
//Team302 includes
#include <interfaces/IChassis.h>
#include <interfaces/IChassis.h>
#include <interfaces/IPrimitive.h>
#include <auton/LiftElevator.h>

class TurnAngle : public IPrimitive {
public:
	TurnAngle();
	virtual ~TurnAngle() = default;

    void Init(PrimitiveParams* params) override;
    void Run() override;
    bool IsDone() override;

private:
	const float PROPORTIONAL_COEFF  = 3.0; //0.5
	const float INTREGRAL_COEFF     = 0.0;
	const float DERIVATIVE_COEFF    = 0.0;
	const float FEET_FORWARD_COEFF  = 0.0;

    IChassis* m_chassis;
    LiftElevator* m_lift;
    float m_targetAngle;
    float m_maxTimeout;
    float m_leftPos;
    float m_rightPos;
    bool m_isDone;

    const float ANGLE_THRESH = 2; // +/- threshold for being at angle
    const float MAX_VELOCITY = 20; //inches per second
    const float MIN_VELOCITY = 4;
    const float ANGLE_DIFFERENCE_VELOCITY_MULTIPLIER = 0.7;
};

#endif /* SRC_AUTON_TURNANGLE_H_ */
