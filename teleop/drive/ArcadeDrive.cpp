/*
 * ArcadeDrive.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: jonah
 */
#include <cmath>

#include <factories/ChassisFactory.h>
#include <interfaces/IChassis.h>
#include <teleop/controllers/TeleopControl.h>
#include <teleop/drive/ArcadeDrive.h>
#include <utils/LimitValue.h>


//--------------------------------------------------------------------
// Method:      ArcadeDrive <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
ArcadeDrive::ArcadeDrive() : IDrive()
{
    // Set the profile to cubic on the joysticks being used
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::ARCADE_DRIVE_STEER, AXIS_SENSITIVITY_CURVE::AXIS_CUBIC );
	TeleopControl::GetInstance()->SetAxisScaleFactor(TeleopControl::ARCADE_DRIVE_STEER, 0.90 );
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::ARCADE_DRIVE_THROTTLE, AXIS_SENSITIVITY_CURVE::AXIS_CUBIC );
}

void ArcadeDrive::Drive()
{
	//Set chassis power according to OI's inputs
//    printf( "==>> Arcade Drive Throttle %g Steer %g \n" , TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ARCADE_DRIVE_THROTTLE ),
//                                                          TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ARCADE_DRIVE_STEER ) );
//
    float leftSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ARCADE_DRIVE_THROTTLE ) + TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ARCADE_DRIVE_STEER ) ;
    float rightSpeed = TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ARCADE_DRIVE_THROTTLE ) - TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ARCADE_DRIVE_STEER );

    float leftvalue= LimitValue::ForceInRange( leftSpeed, -1.0,1.0 );
    float leftvaluetrimmed= LimitValue::GetTrimmedValue( leftSpeed, -1.0,1.0 );

    float rightvalue= LimitValue::ForceInRange( rightSpeed, -1.0,1.0 );
    float rightvaluetrimmed= LimitValue::GetTrimmedValue( rightSpeed, -1.0,1.0 );

//    printf( "==>> limited %g %g \n", leftvalue, rightvalue );
//    printf( "==>> trimmed %g %g \n", leftvaluetrimmed, rightvaluetrimmed );


    //::  Set the motor speeds as follows:
    //          left motor speed = limited left motor speed - right speed amount out of range
    //          right motor speed = limited right motor speed - left speed amount out of range
    double leftmotorspeed = leftvalue - rightvaluetrimmed;

    double rightmotorspeed = rightvalue - leftvaluetrimmed;
    double maxValue = 0.0;
    if ( std::abs(leftmotorspeed) > maxValue )
    {
        maxValue = std::abs( leftmotorspeed );
    }
    if ( std::abs(rightmotorspeed) > maxValue )
    {
        maxValue = std::abs( rightmotorspeed );
    }
    //Scale down all values if max > 1.0
    if ( maxValue > 1.0 )
    {
        leftmotorspeed /= maxValue;
        rightmotorspeed /= maxValue;
    }

//    printf( "==>> speeds %g %g \n", leftmotorspeed, rightmotorspeed );

    ChassisFactory::GetIChassis()->SetTalonMode(DragonTalon::PERCENT);
    ChassisFactory::GetIChassis()->SetLeftRightMagnitudes( leftmotorspeed, rightmotorspeed );
 //    ChassisFactory::GetIChassis()->SetDriveMagnitudes( TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ARCADE_DRIVE_STEER ),
//                                                       TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ARCADE_DRIVE_THROTTLE ),
//                                                       0.0 );
}


const char* ArcadeDrive::GetIdentifier() const
{
    return "Arcade Drive \n";
}
