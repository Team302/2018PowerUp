/*
 * DragonNavX.h
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONNAVX_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONNAVX_H_

#include <AHRS.h>
//#include <ITimestampedDataSubscriber.h>

class DragonNavX
{

	public:
	enum NAVX_PORT_TYPE
	{
		SPI,
		I2C,
		SERIAL,
		MAX_NAVX_PORTS
	};


		DragonNavX() = delete;
		DragonNavX
		(
			DragonNavX::NAVX_PORT_TYPE		portType,
			int								portID,
			int								updateRate

		);
		virtual ~DragonNavX() = default;


		virtual float  GetPitch() = 0;
		virtual float  GetRoll() = 0;
		virtual float  GetYaw() = 0;
		virtual float  GetCompassHeading() = 0;

		void   ZeroYaw();
		bool   IsCalibrating();
		bool   IsConnected();
		double GetByteCount();
		double GetUpdateCount();
		long   GetLastSensorTimestamp();

		virtual float  GetWorldLinearAccelX() = 0;
		virtual float  GetWorldLinearAccelY() = 0;
		virtual float  GetWorldLinearAccelZ() = 0;
		virtual bool   IsMoving() = 0;
		virtual bool   IsRotating() = 0;

		float  GetBarometricPressure();
		float  GetAltitude();
		bool   IsAltitudeValid();

		virtual float  GetFusedHeading() = 0;

		bool   IsMagneticDisturbance();
		bool   IsMagnetometerCalibrated();

		virtual float  GetQuaternionW() = 0;
		virtual float  GetQuaternionX() = 0;
		virtual float  GetQuaternionY() = 0;
		virtual float  GetQuaternionZ() = 0;

		void   ResetDisplacement();

		virtual void   UpdateDisplacement
		(
			float accel_x_g,
			float accel_y_g,
			int update_rate_hz,
			bool is_moving
		) = 0;
		virtual float  GetVelocityX() = 0;
		virtual float  GetVelocityY() = 0;
		virtual float  GetVelocityZ() = 0;
		virtual float  GetDisplacementX() = 0;
		virtual float  GetDisplacementY() = 0;
		virtual float  GetDisplacementZ() = 0;
		virtual double GetAngle() = 0;
		virtual double GetRate() = 0;
		virtual void   SetAngleAdjustment
		(
			double angle
		) = 0;
		virtual double GetAngleAdjustment() = 0;

		void   Reset();

		virtual float  GetRawGyroX() = 0;
		virtual float  GetRawGyroY() = 0;
		virtual float  GetRawGyroZ() = 0;
		virtual float  GetRawAccelX() = 0;
		virtual float  GetRawAccelY() = 0;
		virtual float  GetRawAccelZ() = 0;
		virtual float  GetRawMagX() = 0;
		virtual float  GetRawMagY() = 0;
		virtual float  GetRawMagZ() = 0;


		float  GetPressure();
		float  GetTempC();
		AHRS::BoardYawAxis GetBoardYawAxis();
		std::string GetFirmwareVersion();
/*
		bool RegisterCallback
		(
			ITimestampedDataSubscriber *callback,
			void *callback_context
		);
		bool DeregisterCallback
		(
			ITimestampedDataSubscriber *callback
		);
*/
		int GetActualUpdateRate();
		int GetRequestedUpdateRate();

		void EnableLogging(bool enable);

	protected:
		inline AHRS* GetNavX() const { return m_navX; }

	private:
		void ProcessSPI
		(
			DragonNavX::NAVX_PORT_TYPE		portType,
			int								portID,
			int								updateRate

		);
		void ProcessI2C
		(
			DragonNavX::NAVX_PORT_TYPE		portType,
			int								portID,
			int								updateRate

		);
		void ProcessSerial
		(
			DragonNavX::NAVX_PORT_TYPE		portType,
			int								portID,
			int								updateRate

		);
		AHRS*		m_navX;					// referenced NavX sensor


};

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONNAVX_H_ */
