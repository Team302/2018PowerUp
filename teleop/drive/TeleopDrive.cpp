/*
 * TeleopDrive.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: jonah
 */

#include <factories/ChassisFactory.h>
#include <interfaces/IChassis.h>
#include <teleop/controllers/TeleopControl.h>
#include <teleop/drive/TeleopDrive.h>

TeleopDrive::TeleopDrive() : IDrive()
{
    // Set the profile to cubic on the joysticks being used
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::ROBOT_X_MAGNITUDE, AXIS_SENSITIVITY_CURVE::AXIS_CUBIC );
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::ROBOT_Y_MAGNITUDE, AXIS_SENSITIVITY_CURVE::AXIS_CUBIC );
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::ROBOT_ROTATION_MAGNITUDE, AXIS_SENSITIVITY_CURVE::AXIS_CUBIC );
}

void TeleopDrive::Drive()
{
	ChassisFactory::GetIChassis()->EnableCurrentLimiting(true);
	ChassisFactory::GetIChassis()->SetTalonMode( DragonTalon::PERCENT );
	//Set chassis power according to OI's inputs
	ChassisFactory::GetIChassis()->SetDriveMagnitudes(
	TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_X_MAGNITUDE ),
	TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_Y_MAGNITUDE ),
	TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_ROTATION_MAGNITUDE ));
}

const char* TeleopDrive::GetIdentifier() const
{
    return "Increased turn control at high speeds mode \n";
}

