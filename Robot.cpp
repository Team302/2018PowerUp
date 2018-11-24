/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// C++ Library includes
#include <iostream>
#include <string>

// WPILIB includes
#include <CameraServer.h>
#include <Compressor.h>
#include <IterativeRobot.h>
#include <Robot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>


//Team302 includes
#include <auton/CyclePrimitives.h>
#include <auton/PrimitiveEnums.h>

#include <factories/ChassisFactory.h>
#include <factories/MechanismFactory.h>
#include <factories/CompressorFactory.h>
#include <factories/LidarFactory.h>

#include <interfaces/IChassis.h>
#include <interfaces/IMechanism.h>

#include <subsys/mechanisms/Lift.h>
#include <subsys/xmlParsing/RobotDefn.h>

#include <teleop/controllers/TeleopControl.h>
#include <teleop/drive/TeleopDriveControl.h>
#include <teleop/controlMechanisms/CubeHandler.h>
#include <teleop/controlMechanisms/ClimbHandler.h>

// temporary
#include <interfaces/IDragonController.h>
#include <teleop/controllers/DragonGamepad.h>


//===========================================================================================
// Method:			RobotInit
// Description:		Initializes the robot when it it turned on (it is only run once).
//                  This is where class attributes are created, so that they can be used
// 					by all of the methods in the class.
//===========================================================================================
void Robot::RobotInit()
{
	LEDFactory::GetFactory()->CreateLEDs(31); // 1
//    printf( "RobotInit \n" );		// Debugging

//    m_dragongamepad = new DragonGamepad(4);     // Temporary testing

    // Read the robot definition from the xml configuration files and
    // create the hardware (chassis + mechanisms along with their talons,
    // solenoids, digital inputs, analog inputs, etc.
    RobotDefn::ParseXML();

//  Now in XML - saving here until tested
    CameraServer* server = CameraServer::GetInstance();
    if ( server != nullptr )
    {
        cs::UsbCamera camera = server->StartAutomaticCapture();
//                camera.SetVideoMode( cs::VideoMode::kMJPEG, 640, 360, 15 );
        camera.SetVideoMode( cs::VideoMode::kMJPEG, 320, 180, 20 );
    }

    // Display the autonomous choices on the dashboard for selection.
    m_cyclePrims = new CyclePrimitives();
//    ChassisFactory::GetIChassis()->ResetGyro();
}

//===========================================================================================
// Method:		DisabledInit
// Description:	Called whenever the robot gets disabled (once when it gets disabled).
//===========================================================================================
void Robot::DisabledInit()
{
//    printf( "DisabledInit \n" );		// Debugging

    // Turn off compressor
    Compressor* compress = CompressorFactory::GetFactory()->GetCompressor();
    if ( compress != nullptr )
    {
        compress->Stop();
    }

//		    AutonSelector
    //TODO: clear out primitive parameters
    if (m_ledHandler != nullptr)
    {
    	m_ledHandler->DisabledLED();
    }
}

//===========================================================================================
// Method:		DisabledPeriodic
// Description:	Called every 20 milliseconds when the robot is disabled.
//===========================================================================================
void Robot::DisabledPeriodic()
{
    //	printf( "DisabledPeriodic \n" );
}


//===========================================================================================
// Method:		AutonomousInit
// Description: Initialized autonomous (called once when autonomous starts).  It uses the
// 				chooser created in RobotInit to select the desires autonomous routine.
//===========================================================================================
void Robot::AutonomousInit()
{
	printf("Auton init\n");
    //--------------------------------------------------------------------------------------------
    // Make sure the Compressor is running
    //--------------------------------------------------------------------------------------------
    ChassisFactory::GetIChassis()->ResetChassis();
    ChassisFactory::GetIChassis()->EnableCurrentLimiting(true);
    printf("after enabled current limiting\n");

    m_lift = (dynamic_cast<Lift*>(MechanismFactory::GetMechanismFactory()->GetIMechanism(IMechanism::LIFT)));
    if (m_lift != nullptr)
    {
    	m_lift->ReleaseLatch();
    }

    printf("after release latch\n");
//    Compressor* compress = CompressorFactory::GetFactory()->GetCompressor();
//    if ( compress != nullptr )
//    {
//        compress->Start();
//    }

    if (LidarFactory::GetLidarFactory()->GetLidar( DragonLidar::FORWARD_GRABBER ) != nullptr)
    {
        printf("lidar is not null \n");
        ///////////Testing LIDAR
        frc::SmartDashboard::PutNumber("forward LIDAR", LidarFactory::GetLidarFactory()->GetLidar( DragonLidar::FORWARD_GRABBER )->GetDistance());
//        printf("FORWARD LIDAR %g \n", LidarFactory::GetLidarFactory()->GetLidar( DragonLidar::FORWARD_GRABBER )->GetDistance());
    }
    else
    {
        printf("lidar is NULL! \n");
    }



    // run selected auton option
    m_cyclePrims->Init();
//    m_ledHandler = new LEDHandler();
    if (m_ledHandler != nullptr)
    {
    	m_ledHandler->AutonLED();
    } else {
    	printf("Led handler is NULL! \n");
    }
}

//===========================================================================================
// Method:  		AutonomousPeriodic
// Description:		Run the selected autonomous routine (every 20 milliseconds)
//===========================================================================================
void Robot::AutonomousPeriodic()
{
    //printf( "AutonPeriodic \n" );
    if (m_ledHandler != nullptr)
    {
    	m_ledHandler->AutonLED();
    } else {
//    	printf("Led handler is NULL! \n");
    }
    //Real auton magic right here:
    m_cyclePrims->RunCurrentPrimitive();
//    (dynamic_cast<Lift*>(MechanismFactory::GetMechanismFactory()->GetIMechanism(IMechanism::LIFT)))->Periodic();
    if (m_lift != nullptr)
    {
    	m_lift->Periodic();
    }
    frc::SmartDashboard::PutNumber("Chassis current target heading auton: ", ChassisFactory::GetIChassis()->GetTargetHeading());
}


//===========================================================================================
// Method:  		TeleopInit
// Description:		Initializes teleop processing when teleop starts.
//===========================================================================================
void Robot::TeleopInit()
{
//    printf( "TeleopInit \n" );		// debugging

    // Teleop Control
    m_teleopDriveControl = new TeleopDriveControl();
    m_cubeHandler = new CubeHandler();
    m_climbHandler = new ClimbHandler();
//            m_cubeHandler->ResetHeight(); //TODO: use this when we want the elevator to automatically go down in teleop.

    // Make sure the Compressor is running
    CompressorFactory* factory = CompressorFactory::GetFactory();
    if ( factory != nullptr )
    {
        Compressor* compress = factory->GetCompressor();
        if ( compress != nullptr )
        {
            compress->Start();
        }
        else
        {
            printf("compressor is NULLPTR! \n");
        }
    }
    else
    {
        printf("compressor factory is NULLPTR! \n");
    }


    ChassisFactory::GetIChassis()->ResetChassis(); //just for testing
    m_ledHandler = new LEDHandler();
    if (m_ledHandler != nullptr)
    {
    	m_ledHandler->TeleopLED();
    } else {
    	printf("Led handler is NULL! \n");
    }
//    DriverStation* ds = &DriverStation::GetInstance();
//    switch (ds->GetAlliance())
//    {
//    case DriverStation::Alliance::kRed:
//    	frc::SmartDashboard::PutString("team color: ", "red");
//    	break;
//    case DriverStation::Alliance::kBlue:
//    	frc::SmartDashboard::PutString("team color: ", "blue");
//    	break;
//    default:
//    	frc::SmartDashboard::PutString("team color: ", "other");
//    	break;
//    }

}


//===========================================================================================
// Method:  		TeleopPeriodic
// Description:		Run robot in teleop mode (every 20 milliseconds)
//===========================================================================================
void Robot::TeleopPeriodic()
{
//				printf( "TeleopPeriodic \n" );		// debugging

    if ( m_teleopDriveControl != nullptr )
    {
        m_teleopDriveControl->Drive();
    }

    ChassisFactory::GetIChassis()->PrintDebug();
    ChassisFactory::GetIChassis()->UpdateChassis(); //update chassis

    if ( m_cubeHandler != nullptr )
    {
        m_cubeHandler->Periodic();
    } else {
//        printf("cube handler is NULL! \n");
    }
    if ( m_climbHandler != nullptr )
    {
        m_climbHandler->Periodic();
    } else {
//        printf("climb handler is NULL! \n");
    }
    if (m_ledHandler != nullptr)
    {
    	m_ledHandler->TeleopLED();
    } else {
//    	printf("Led handler is NULL! \n");
    }
    // TODO:  need to test
    // Put pressure on dashboard

    CompressorFactory* factory = CompressorFactory::GetFactory();
    if ( factory != nullptr )
    {
    	DragonAnalogInput* gauge = factory->GetPressureGauge();
    	if ( gauge != nullptr )
    	{
    		float press = gauge->GetInterpolatedValue();
    		SmartDashboard::PutNumber( "Pressure: ", press );
//    		SmartDashboard::PutBoolean( "Pressure State ", (press>60.0) );
    	}
    }

    // Turn off compressor
    Compressor* compress = CompressorFactory::GetFactory()->GetCompressor();
    if ( compress != nullptr )
    {
        if (compress->Enabled()) {
              m_compressCount++;
              frc::SmartDashboard::PutNumber("compressor enable count: ", m_compressCount);
        }
    }

    if (LidarFactory::GetLidarFactory()->GetLidar( DragonLidar::FORWARD_GRABBER ) != nullptr)
    {
//    	printf("lidar is not null \n");
        ///////////Testing LIDAR
//        frc::SmartDashboard::PutNumber("forward LIDAR", LidarFactory::GetLidarFactory()->GetLidar( DragonLidar::FORWARD_GRABBER )->GetDistance());
//        printf("FORWARD LIDAR %g \n", LidarFactory::GetLidarFactory()->GetLidar( DragonLidar::FORWARD_GRABBER )->GetDistance());
    }
    else
    {
    	printf("lidar is NULL! \n");
    }
}


//===========================================================================================
// Method:  		TestInit
// Description:		Initializes the test environment when test starts
//===========================================================================================
void Robot::TestInit()
{
}


//===========================================================================================
// Method:  		TestPeriodic
// Description:		Run the test routine (every 20 milliseconds)
//===========================================================================================
void Robot::TestPeriodic()
{
    ChassisFactory::GetIChassis()->PrintDebug();
    frc::SmartDashboard::PutNumber("forward LIDAR", LidarFactory::GetLidarFactory()->GetLidar( DragonLidar::FORWARD_GRABBER )->GetDistance());
//    printf("FORWARD LIDAR %g \n", LidarFactory::GetLidarFactory()->GetLidar( DragonLidar::FORWARD_GRABBER )->GetDistance());
}

START_ROBOT_CLASS(Robot)
