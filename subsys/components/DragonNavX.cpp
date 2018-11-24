/*
 * DragonNavX.cpp
 */

#include <subsys/components/DragonNavX.h>


#include <AHRS.h>
#include <I2C.h>
#include <SerialPort.h>
#include <SPI.h>
//#include <ITimestampedDataSubscriber.h>

using namespace frc;

	DragonNavX::DragonNavX
	(
		DragonNavX::NAVX_PORT_TYPE		portType,
		int								portID,
		int								updateRate

	)
	{
		switch ( portType )
		{
			case DragonNavX::SPI:
				ProcessSPI( portType, portID, updateRate );
				break;

			case DragonNavX::I2C:
				ProcessI2C( portType, portID, updateRate );
				break;

			case DragonNavX::SERIAL:
				ProcessSerial( portType, portID, updateRate );
				break;

			default:
				printf( "==>> DragonNavX::DragonNavX unknown port type \n" );
				break;
		}

	}


	void DragonNavX::ProcessSPI
	(
		DragonNavX::NAVX_PORT_TYPE		portType,
		int								portID,
		int								updateRate

	)
	{
			SPI::Port spiPort = SPI::kOnboardCS0;
			switch ( portID )
			{
				case 0:
					spiPort = SPI::kOnboardCS0;
					break;

				case 1:
					spiPort = SPI::kOnboardCS1;
					break;

				case 2:
					spiPort = SPI::kOnboardCS2;
					break;

				case 3:
					spiPort = SPI::kOnboardCS3;
					break;

				case 4:
					spiPort = SPI::kMXP;
					break;

				default:
					printf( "==>> DragonNavX::DragonNavX invalid SPI port %d \n", portID );
					break;
			}

//			m_navX = new AHRS( spiPort, portID, updateRate );
			m_navX = new AHRS( spiPort, portID );
	}

	void DragonNavX::ProcessI2C
	(
		DragonNavX::NAVX_PORT_TYPE		portType,
		int								portID,
		int								updateRate

	)
	{

		I2C::Port i2cPort = I2C::kOnboard;
		switch ( portID )
		{
			case 0:
				i2cPort = I2C::kOnboard;
				break;

			case 1:
				i2cPort = I2C::kMXP;
				break;

			default:
				printf( "==>> DragonNavX::DragonNavX invalid I2C port %d \n", portID );
				break;

		}
//		m_navX = new AHRS( i2cPort, portID, updateRate );
		m_navX = new AHRS( i2cPort, portID );
	}


	void DragonNavX::ProcessSerial
	(
		DragonNavX::NAVX_PORT_TYPE		portType,
		int								portID,
		int								updateRate

	)
	{
		return;
	}


	void   DragonNavX::ZeroYaw()
	{
		if ( m_navX != nullptr )
		{
			m_navX->ZeroYaw();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
	}
	bool   DragonNavX::IsCalibrating()
	{
		bool calibrating = false;
		if ( m_navX != nullptr )
		{
			calibrating = m_navX->IsCalibrating();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return calibrating;
	}
	bool   DragonNavX::IsConnected()
	{
		float connected = 0.0;
		if ( m_navX != nullptr )
		{
			connected = m_navX->IsConnected();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return connected;
	}
	double DragonNavX::GetByteCount()
	{
		double byteCount = 0.0;
		if ( m_navX != nullptr )
		{
			byteCount = m_navX->GetByteCount();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return byteCount;
	}
	double DragonNavX::GetUpdateCount()
	{
		double updateCount = 0.0;
		if ( m_navX != nullptr )
		{
			updateCount = m_navX->GetUpdateCount();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return updateCount;
	}
	long   DragonNavX::GetLastSensorTimestamp()
	{
		long timeStamp = 0.0;
		if ( m_navX != nullptr )
		{
			timeStamp = m_navX->GetLastSensorTimestamp();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return timeStamp;
	}


	float  DragonNavX::GetBarometricPressure()
	{
		float press = 0.0;
		if ( m_navX != nullptr )
		{
			press = m_navX->GetBarometricPressure();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return press;
	}
	float  DragonNavX::GetAltitude()
	{
		float alt = 0.0;
		if ( m_navX != nullptr )
		{
			alt = m_navX->GetAltitude();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return alt;
	}
	bool   DragonNavX::IsAltitudeValid()
	{
		bool valid = false;
		if ( m_navX != nullptr )
		{
			valid = m_navX->IsAltitudeValid();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return valid;
	}


	bool   DragonNavX::IsMagneticDisturbance()
	{
		bool disturbance = 0.0;
		if ( m_navX != nullptr )
		{
			disturbance = m_navX->IsMagneticDisturbance();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return disturbance;
	}
	bool   DragonNavX::IsMagnetometerCalibrated()
	{
		bool calibrated = false;
		if ( m_navX != nullptr )
		{
			calibrated = m_navX->IsMagnetometerCalibrated();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return calibrated;
	}

	void   DragonNavX::ResetDisplacement()
	{
		if ( m_navX != nullptr )
		{
			m_navX->ResetDisplacement();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
	}

	void   DragonNavX::Reset()
	{
		if ( m_navX != nullptr )
		{
			m_navX->Reset();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
	}

	float  DragonNavX::GetPressure()
	{
		float pitch = 0.0;
		if ( m_navX != nullptr )
		{
			pitch = m_navX->GetPitch();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return pitch;
	}
	float  DragonNavX::GetTempC()
	{
		float temp = 0.0;
		if ( m_navX != nullptr )
		{
			temp = m_navX->GetTempC();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return temp;
	}
	AHRS::BoardYawAxis DragonNavX::GetBoardYawAxis()
	{
		AHRS::BoardYawAxis axis;
		if ( m_navX != nullptr )
		{
			axis = m_navX->GetBoardYawAxis();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return axis;
	}
	std::string DragonNavX::GetFirmwareVersion()
	{
		std::string version;
		if ( m_navX != nullptr )
		{
			version = m_navX->GetFirmwareVersion();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return version;
	}

	int DragonNavX::GetActualUpdateRate()
	{
		int rate = 0.0;
		if ( m_navX != nullptr )
		{
			rate = m_navX->GetActualUpdateRate();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return rate;
	}
	int DragonNavX::GetRequestedUpdateRate()
	{
		int rate = 0.0;
		if ( m_navX != nullptr )
		{
			rate = m_navX->GetRequestedUpdateRate();
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
		return rate;

	}

	void DragonNavX::EnableLogging(bool enable)
	{
		if ( m_navX != nullptr )
		{
			m_navX->EnableLogging( enable );
		}
		else
		{
//			printf( "navx not initialized \n" );
		}
	}

