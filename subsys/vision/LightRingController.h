/*
 * LightRingController.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Austin
 */

#ifndef SRC_SUBSYS_VISION_LIGHTRINGCONTROLLER_H_
#define SRC_SUBSYS_VISION_LIGHTRINGCONTROLLER_H_

#include <PWM.h>

class LightRingController
{
public:
	enum TYPE
	{
		RGB,
		STATIC
	};

	void setOnOff( int type, bool on );

	LightRingController();
	virtual ~LightRingController() = default;
private:
	// PWMs
	frc::PWM* m_redChannel;
	frc::PWM* m_greenChannel;
	frc::PWM* m_blueChannel;
	// consts
	const int RED_VALUE = 50000;
	const int GREEN_VALUE = 50000;
	const int BLUE_VALUE = 50000;
};

#endif /* SRC_SUBSYS_VISION_LIGHTRINGCONTROLLER_H_ */
