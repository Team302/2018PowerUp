/*
 * DragonNavXLogoBack.cpp
 *
 */

#include <subsys/components/DragonNavXLogoBack.h>

#include <subsys/components/DragonNavX.h>

#include <AHRS.h>
#include <I2C.h>
#include <SerialPort.h>
#include <SPI.h>

using namespace frc;

	DragonNavXLogoBack::DragonNavXLogoBack
	(
		DragonNavX::NAVX_PORT_TYPE		portType,
		int								portID,
		int								updateRate

	) : DragonNavX( portType, portID, updateRate )
	{
	}


	float  DragonNavXLogoBack::GetPitch()
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
	float  DragonNavXLogoBack::GetRoll()
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
	float  DragonNavXLogoBack::GetYaw()
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
	float  DragonNavXLogoBack::GetCompassHeading()
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


	float  DragonNavXLogoBack::GetWorldLinearAccelX()
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
	float  DragonNavXLogoBack::GetWorldLinearAccelY()
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
	float  DragonNavXLogoBack::GetWorldLinearAccelZ()
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
	bool   DragonNavXLogoBack::IsMoving()
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
	bool   DragonNavXLogoBack::IsRotating()
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


	float  DragonNavXLogoBack::GetFusedHeading()
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


	float  DragonNavXLogoBack::GetQuaternionW()
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
	float  DragonNavXLogoBack::GetQuaternionX()
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
	float  DragonNavXLogoBack::GetQuaternionY()
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
	float  DragonNavXLogoBack::GetQuaternionZ()
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

	void   DragonNavXLogoBack::UpdateDisplacement
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
	float  DragonNavXLogoBack::GetVelocityX()
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
	float  DragonNavXLogoBack::GetVelocityY()
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
	float  DragonNavXLogoBack::GetVelocityZ()
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
	float  DragonNavXLogoBack::GetDisplacementX()
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
	float  DragonNavXLogoBack::GetDisplacementY()
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
	float  DragonNavXLogoBack::GetDisplacementZ()
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
	double DragonNavXLogoBack::GetAngle()
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
	double DragonNavXLogoBack::GetRate()
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
	void   DragonNavXLogoBack::SetAngleAdjustment
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
	double DragonNavXLogoBack::GetAngleAdjustment()
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

	float  DragonNavXLogoBack::GetRawGyroX()
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
	float  DragonNavXLogoBack::GetRawGyroY()
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
	float  DragonNavXLogoBack::GetRawGyroZ()
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
	float  DragonNavXLogoBack::GetRawAccelX()
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
	float  DragonNavXLogoBack::GetRawAccelY()
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
	float  DragonNavXLogoBack::GetRawAccelZ()
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
	float  DragonNavXLogoBack::GetRawMagX()
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
	float  DragonNavXLogoBack::GetRawMagY()
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
	float  DragonNavXLogoBack::GetRawMagZ()
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
