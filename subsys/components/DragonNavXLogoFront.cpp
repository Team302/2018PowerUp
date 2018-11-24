/*
 * DragonNavXLogoFront.cpp
 */

#include <subsys/components/DragonNavXLogoFront.h>


#include <subsys/components/DragonNavX.h>

#include <AHRS.h>
#include <I2C.h>
#include <SerialPort.h>
#include <SPI.h>

using namespace frc;

	DragonNavXLogoFront::DragonNavXLogoFront
	(
		DragonNavX::NAVX_PORT_TYPE		portType,
		int								portID,
		int								updateRate

	) : DragonNavX( portType, portID, updateRate )
	{
	}


	float  DragonNavXLogoFront::GetPitch()
	{
		float pitch = 0.0;
		if ( GetNavX() != nullptr )
		{
			pitch = -1.0* GetNavX()->GetPitch();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return pitch;
	}
	float  DragonNavXLogoFront::GetRoll()
	{
		float roll = 0.0;
		if ( GetNavX() != nullptr )
		{
			roll = -1.0 * GetNavX()->GetRoll();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return roll;
	}
	float  DragonNavXLogoFront::GetYaw()
	{
		float yaw = 0.0;
		if ( GetNavX() != nullptr )
		{
			yaw = -1.0 * GetNavX()->GetYaw();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return yaw;
	}
	float  DragonNavXLogoFront::GetCompassHeading()
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

	float  DragonNavXLogoFront::GetWorldLinearAccelX()
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
	float  DragonNavXLogoFront::GetWorldLinearAccelY()
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
	float  DragonNavXLogoFront::GetWorldLinearAccelZ()
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
	bool   DragonNavXLogoFront::IsMoving()
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
	bool   DragonNavXLogoFront::IsRotating()
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

	float  DragonNavXLogoFront::GetFusedHeading()
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

	float  DragonNavXLogoFront::GetQuaternionW()
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
	float  DragonNavXLogoFront::GetQuaternionX()
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
	float  DragonNavXLogoFront::GetQuaternionY()
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
	float  DragonNavXLogoFront::GetQuaternionZ()
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

	void   DragonNavXLogoFront::UpdateDisplacement
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
	float  DragonNavXLogoFront::GetVelocityX()
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
	float  DragonNavXLogoFront::GetVelocityY()
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
	float  DragonNavXLogoFront::GetVelocityZ()
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
	float  DragonNavXLogoFront::GetDisplacementX()
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
	float  DragonNavXLogoFront::GetDisplacementY()
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
	float  DragonNavXLogoFront::GetDisplacementZ()
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
	double DragonNavXLogoFront::GetAngle()
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
	double DragonNavXLogoFront::GetRate()
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
	void   DragonNavXLogoFront::SetAngleAdjustment
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
	double DragonNavXLogoFront::GetAngleAdjustment()
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

	float  DragonNavXLogoFront::GetRawGyroX()
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
	float  DragonNavXLogoFront::GetRawGyroY()
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
	float  DragonNavXLogoFront::GetRawGyroZ()
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
	float  DragonNavXLogoFront::GetRawAccelX()
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
	float  DragonNavXLogoFront::GetRawAccelY()
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
	float  DragonNavXLogoFront::GetRawAccelZ()
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
	float  DragonNavXLogoFront::GetRawMagX()
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
	float  DragonNavXLogoFront::GetRawMagY()
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
	float  DragonNavXLogoFront::GetRawMagZ()
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

