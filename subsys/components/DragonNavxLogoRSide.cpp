/*
 * DragonNavxLogoRSide.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: joewi
 */

#include <subsys/components/DragonNavxLogoRSide.h>

#include <subsys/components/DragonNavX.h>
#include <AHRS.h>
#include <I2C.h>
#include <SerialPort.h>
#include <SPI.h>

using namespace frc;

	DragonNavXLogoRSide::DragonNavXLogoRSide
	(
		DragonNavX::NAVX_PORT_TYPE		portType,
		int								portID,
		int								updateRate

	) : DragonNavX( portType, portID, updateRate )
	{
	}


	float  DragonNavXLogoRSide::GetPitch()
	{
		float pitch = 0.0;
		if ( GetNavX() != nullptr )
		{
			pitch = GetNavX()->GetPitch();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return pitch;
	}
	float  DragonNavXLogoRSide::GetRoll()
	{
		float roll = 0.0;
		if ( GetNavX() != nullptr )
		{
			roll = GetNavX()->GetRoll();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return roll;
	}
	float  DragonNavXLogoRSide::GetYaw()
	{
		float yaw = 0.0;
		if ( GetNavX() != nullptr )
		{
			yaw = GetNavX()->GetYaw();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return yaw;
	}
	float  DragonNavXLogoRSide::GetCompassHeading()
	{
		float heading = 0.0;
		if ( GetNavX() != nullptr )
		{
			heading = GetNavX()->GetCompassHeading();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return heading;
	}

	float  DragonNavXLogoRSide::GetWorldLinearAccelX()
	{
		float accel = 0.0;
		if ( GetNavX() != nullptr )
		{
			accel = GetNavX()->GetWorldLinearAccelX();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return accel;
	}
	float  DragonNavXLogoRSide::GetWorldLinearAccelY()
	{
		float accel = 0.0;
		if ( GetNavX() != nullptr )
		{
			accel = GetNavX()->GetWorldLinearAccelY();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return accel;
	}
	float  DragonNavXLogoRSide::GetWorldLinearAccelZ()
	{
		float accel = 0.0;
		if ( GetNavX() != nullptr )
		{
			accel = GetNavX()->GetWorldLinearAccelZ();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return accel;
	}
	bool   DragonNavXLogoRSide::IsMoving()
	{
		bool moving = false;
		if ( GetNavX() != nullptr )
		{
			moving = GetNavX()->IsMoving();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return moving;
	}
	bool   DragonNavXLogoRSide::IsRotating()
	{
		bool rotating = false;
		if ( GetNavX() != nullptr )
		{
			rotating = GetNavX()->IsRotating();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return rotating;
	}

	float  DragonNavXLogoRSide::GetFusedHeading()
	{
		float heading = 0.0;
		if ( GetNavX() != nullptr )
		{
			heading = GetNavX()->GetFusedHeading();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return heading;
	}

	float  DragonNavXLogoRSide::GetQuaternionW()
	{
		float val = 0.0;
		if ( GetNavX() != nullptr )
		{
			val = GetNavX()->GetQuaternionW();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return val;
	}
	float  DragonNavXLogoRSide::GetQuaternionX()
	{
		float val = 0.0;
		if ( GetNavX() != nullptr )
		{
			val = GetNavX()->GetQuaternionX();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return val;
	}
	float  DragonNavXLogoRSide::GetQuaternionY()
	{
		float val = 0.0;
		if ( GetNavX() != nullptr )
		{
			val = GetNavX()->GetQuaternionY();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return val;
	}
	float  DragonNavXLogoRSide::GetQuaternionZ()
	{
		float val = 0.0;
		if ( GetNavX() != nullptr )
		{
			val = GetNavX()->GetQuaternionZ();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return val;
	}

	void   DragonNavXLogoRSide::UpdateDisplacement
	(
		float accel_x_g,
		float accel_y_g,
		int update_rate_hz,
		bool is_moving
	)
	{
		if ( GetNavX() != nullptr )
		{
			GetNavX()->UpdateDisplacement( accel_x_g, accel_y_g, update_rate_hz, is_moving );
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
	}
	float  DragonNavXLogoRSide::GetVelocityX()
	{
		float vel = 0.0;
		if ( GetNavX() != nullptr )
		{
			vel = GetNavX()->GetVelocityX();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return vel;
	}
	float  DragonNavXLogoRSide::GetVelocityY()
	{
		float vel = 0.0;
		if ( GetNavX() != nullptr )
		{
			vel = GetNavX()->GetVelocityY();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return vel;
	}
	float  DragonNavXLogoRSide::GetVelocityZ()
	{
		float vel = 0.0;
		if ( GetNavX() != nullptr )
		{
			vel = GetNavX()->GetVelocityZ();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return vel;
	}
	float  DragonNavXLogoRSide::GetDisplacementX()
	{
		float disp = 0.0;
		if ( GetNavX() != nullptr )
		{
			disp = GetNavX()->GetDisplacementX();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return disp;
	}
	float  DragonNavXLogoRSide::GetDisplacementY()
	{
		float disp = 0.0;
		if ( GetNavX() != nullptr )
		{
			disp = GetNavX()->GetDisplacementY();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return disp;
	}
	float  DragonNavXLogoRSide::GetDisplacementZ()
	{
		float disp = 0.0;
		if ( GetNavX() != nullptr )
		{
			disp = GetNavX()->GetDisplacementZ();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return disp;
	}
	double DragonNavXLogoRSide::GetAngle()
	{
		float angle = 0.0;
		if ( GetNavX() != nullptr )
		{
			angle = GetNavX()->GetAngle();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return angle;
	}
	double DragonNavXLogoRSide::GetRate()
	{
		float rate = 0.0;
		if ( GetNavX() != nullptr )
		{
			rate = GetNavX()->GetRate();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return rate;
	}
	void   DragonNavXLogoRSide::SetAngleAdjustment
	(
		double angle
	)
	{
		if ( GetNavX() != nullptr )
		{
			GetNavX()->SetAngleAdjustment( angle );
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
	}
	double DragonNavXLogoRSide::GetAngleAdjustment()
	{
		float angle = 0.0;
		if ( GetNavX() != nullptr )
		{
			angle = GetNavX()->GetAngleAdjustment();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return angle;
	}

	float  DragonNavXLogoRSide::GetRawGyroX()
	{
		float gyro = 0.0;
		if ( GetNavX() != nullptr )
		{
			gyro = GetNavX()->GetRawGyroX();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return gyro;
	}
	float  DragonNavXLogoRSide::GetRawGyroY()
	{
		float gyro = 0.0;
		if ( GetNavX() != nullptr )
		{
			gyro = GetNavX()->GetRawGyroY();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return gyro;
	}
	float  DragonNavXLogoRSide::GetRawGyroZ()
	{
		float gyro = 0.0;
		if ( GetNavX() != nullptr )
		{
			gyro = GetNavX()->GetRawGyroZ();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return gyro;
	}
	float  DragonNavXLogoRSide::GetRawAccelX()
	{
		float acc = 0.0;
		if ( GetNavX() != nullptr )
		{
			acc = GetNavX()->GetRawAccelX();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return acc;
	}
	float  DragonNavXLogoRSide::GetRawAccelY()
	{
		float acc = 0.0;
		if ( GetNavX() != nullptr )
		{
			acc = GetNavX()->GetRawAccelY();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return acc;
	}
	float  DragonNavXLogoRSide::GetRawAccelZ()
	{
		float acc = 0.0;
		if ( GetNavX() != nullptr )
		{
			acc = GetNavX()->GetRawAccelZ();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return acc;
	}
	float  DragonNavXLogoRSide::GetRawMagX()
	{
		float mag = 0.0;
		if ( GetNavX() != nullptr )
		{
			mag = GetNavX()->GetRawMagX();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return mag;
	}
	float  DragonNavXLogoRSide::GetRawMagY()
	{
		float mag = 0.0;
		if ( GetNavX() != nullptr )
		{
			mag = GetNavX()->GetRawMagY();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return mag;
	}
	float  DragonNavXLogoRSide::GetRawMagZ()
	{
		float mag = 0.0;
		if ( GetNavX() != nullptr )
		{
			mag = GetNavX()->GetRawMagZ();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return mag;
	}

