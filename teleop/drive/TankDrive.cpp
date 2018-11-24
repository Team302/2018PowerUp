/*
 * TankDrive.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Chris
 */

#include <factories/ChassisFactory.h>
#include <teleop/drive/TankDrive.h>
#include <teleop/controllers/TeleopControl.h>
#include <teleop/drive/TankDrive.h>
#include <interfaces/IChassis.h>

TankDrive::TankDrive() : IDrive()
{
    // Set the profile to cubic on the joysticks being used
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::TANK_DRIVE_LEFT_CONTROL, AXIS_SENSITIVITY_CURVE::AXIS_CUBIC );
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::TANK_DRIVE_RIGHT_CONTROL, AXIS_SENSITIVITY_CURVE::AXIS_CUBIC );
}

void TankDrive::Drive()
{
	ChassisFactory::GetIChassis()->SetTalonMode(DragonTalon::PERCENT);
	ChassisFactory::GetIChassis()->SetLeftRightMagnitudes( TeleopControl::GetInstance()->GetAxisValue( TeleopControl::TANK_DRIVE_LEFT_CONTROL ),
												           TeleopControl::GetInstance()->GetAxisValue( TeleopControl::TANK_DRIVE_RIGHT_CONTROL )	);
}

const char* TankDrive::GetIdentifier() const
{
    return "Tank Drive \n";
}

