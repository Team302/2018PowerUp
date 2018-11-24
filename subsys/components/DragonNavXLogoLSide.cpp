/*
 * DragonNavXLogoLSide.cpp
 */

#include <subsys/components/DragonNavXLogoLSide.h>
#include <subsys/components/DragonNavX.h>


#include <AHRS.h>
#include <I2C.h>
#include <SerialPort.h>
#include <SPI.h>

using namespace frc;

	DragonNavXLogoLSide::DragonNavXLogoLSide
	(
		DragonNavX::NAVX_PORT_TYPE		portType,
		int								portID,
		int								updateRate

	) : DragonNavX( portType, portID, updateRate )
	{
	}


	float  DragonNavXLogoLSide::GetPitch()
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
	float  DragonNavXLogoLSide::GetRoll()
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
	float  DragonNavXLogoLSide::GetYaw()
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
	float  DragonNavXLogoLSide::GetCompassHeading()
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

	float  DragonNavXLogoLSide::GetWorldLinearAccelX()
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
	float  DragonNavXLogoLSide::GetWorldLinearAccelY()
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
	float  DragonNavXLogoLSide::GetWorldLinearAccelZ()
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
	bool   DragonNavXLogoLSide::IsMoving()
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
	bool   DragonNavXLogoLSide::IsRotating()
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

	float  DragonNavXLogoLSide::GetFusedHeading()
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

	float  DragonNavXLogoLSide::GetQuaternionW()
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
	float  DragonNavXLogoLSide::GetQuaternionX()
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
	float  DragonNavXLogoLSide::GetQuaternionY()
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
	float  DragonNavXLogoLSide::GetQuaternionZ()
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

	void   DragonNavXLogoLSide::UpdateDisplacement
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
	float  DragonNavXLogoLSide::GetVelocityX()
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
	float  DragonNavXLogoLSide::GetVelocityY()
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
	float  DragonNavXLogoLSide::GetVelocityZ()
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
	float  DragonNavXLogoLSide::GetDisplacementX()
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
	float  DragonNavXLogoLSide::GetDisplacementY()
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
	float  DragonNavXLogoLSide::GetDisplacementZ()
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
	double DragonNavXLogoLSide::GetAngle()
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
	double DragonNavXLogoLSide::GetRate()
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
	void   DragonNavXLogoLSide::SetAngleAdjustment
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
	double DragonNavXLogoLSide::GetAngleAdjustment()
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

	float  DragonNavXLogoLSide::GetRawGyroX()
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
	float  DragonNavXLogoLSide::GetRawGyroY()
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
	float  DragonNavXLogoLSide::GetRawGyroZ()
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
	float  DragonNavXLogoLSide::GetRawAccelX()
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
	float  DragonNavXLogoLSide::GetRawAccelY()
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
	float  DragonNavXLogoLSide::GetRawAccelZ()
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
	float  DragonNavXLogoLSide::GetRawMagX()
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
	float  DragonNavXLogoLSide::GetRawMagY()
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
	float  DragonNavXLogoLSide::GetRawMagZ()
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

