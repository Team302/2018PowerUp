/*
 * Gamepad.h
 *TODO: Document this and the cpp file.
 *  Created on: Jan 31, 2018
 *      Author: Chris
 */

#ifndef SRC_TELEOP_CONTROLLERS_DRAGONGAMEPAD_H_
#define SRC_TELEOP_CONTROLLERS_DRAGONGAMEPAD_H_

#include <interfaces/IDragonController.h>
#include <SmartDashboard/SmartDashboard.h>
#include <utils/LimitValue.h>
#include <Joystick.h>
#include <GenericHID.h>

using namespace frc;

class DragonGamepad : public IDragonController {
public:

	DragonGamepad //constructor
	(
		int		port
	);

	float GetAxisValue
	(
			AXIS_IDENTIFIER	axis
	) const override;

	bool IsButtonPressed
	(
            BUTTON_IDENTIFIER    button         // <I> - button to check
	) const override;

	void SetAxisProfile
	(
			AXIS_IDENTIFIER				axis,
			AXIS_SENSITIVITY_CURVE		curve
	) override;

	void SetAxisScale
	(
			AXIS_IDENTIFIER			axis,
			float					scaleFactor
	) override;

	void FindButtonAxis  //most buttons on the gamepad control axes. this finds out how to find the axis for each button.
	(
		int	m_count
    );

private:

	Joystick* m_gamepad;
//	Joystick* m_joy;
	int m_count;
//	double value;
	// jw - upped array size to 25 so we don't overrun bounds
	const int 		m_maxAxis = 25;
	float			m_axisScale[25];
	float			m_axisInversionFactor[25];
	AXIS_SENSITIVITY_CURVE m_axisProfile[25];
	//DONE: create the things for the axis values.
	// sort by axis instead of button number
	// Axis 0
	const double			button_1_lowerband = 0.118;
	const double			button_1_upperband = 0.1182;
	const int               button_1_axis      = 0;

    const double            button_3_lowerband = 0.102;
    const double            button_3_upperband = 0.10236221;
    const int               button_3_axis      = 0;

    const double            button_6_lowerband = 0.077;
    const double            button_6_upperband = 0.079;
    const int               button_6_axis      = 0;

    const double            button_8_lowerband = 0.054;
    const double            button_8_upperband = 0.056;
    const int               button_8_axis      = 0;

    const double            button_10_lowerband = 0.030;
    const double            button_10_upperband = 0.032;
    const int               button_10_axis      = 0;

    const double            button_12_lowerband = 0.014;
    const double            button_12_upperband = 0.016;
    const int               button_12_axis      = 0;

    // Axis 1
	const double			button_2_lowerband = 0.10;
	const double			button_2_upperband = 0.1182;
	const int               button_2_axis      = 1;

    const double            button_5_lowerband = 0.1023;
    const double            button_5_upperband = 0.1026223;
    const int               button_5_axis      = 1;

    const double			button_4_lowerband = 0.077;
	const double			button_4_upperband = 0.08;
    const int               button_4_axis      = 1;

	const double			button_7_lowerband = 0.054;
	const double			button_7_upperband = 0.056;
    const int               button_7_axis      = 1;

	const double			button_9_lowerband = 0.03;
	const double			button_9_upperband = 0.032;
    const int               button_9_axis      = 1;

	const double 			button_11_lowerband = 0.014;
	const double			button_11_upperband = 0.016;
    const int               button_11_axis      = 1;




};

#endif /* SRC_TELEOP_CONTROLLERS_DRAGONGAMEPAD_H_ */
