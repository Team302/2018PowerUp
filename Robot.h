/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <string>

// WPILIB includes
#include <IterativeRobot.h>
#include <SmartDashboard/SendableChooser.h>


//Team302 includes
#include <auton/CyclePrimitives.h>
#include <auton/PrimitiveEnums.h>

#include <teleop/drive/TeleopDriveControl.h>
#include <teleop/controlMechanisms/CubeHandler.h>
#include <teleop/controlMechanisms/ClimbHandler.h>
#include <teleop/controlMechanisms/LEDHandler.h>

// temporary
#include <teleop/controllers/DragonGamepad.h>


class Robot : public frc::IterativeRobot
{
public:
	void RobotInit() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void TestInit() override;
	void TestPeriodic() override;

private:

    frc::SendableChooser<std::string>   m_autonChooser;                     // Auton mode selector
    const std::string                   m_autoNameDefault = "Default";      // Default auton option
    const std::string                   m_autoNameCustom = "My Auto";       // Custom auton option
    std::string                         m_autoSelected;                     // Selected auton mode

    CyclePrimitives* m_cyclePrims;

    TeleopDriveControl* m_teleopDriveControl;

    CubeHandler* m_cubeHandler;
    LEDHandler* m_ledHandler;
    ClimbHandler* m_climbHandler;
    Lift* m_lift;

    int m_compressCount;

    DragonGamepad* m_dragongamepad;             // temporary

};
