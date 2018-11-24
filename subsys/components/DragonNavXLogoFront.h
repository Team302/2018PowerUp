/*
 * DragonNavXLogoFront.h
 *
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONNAVXLOGOFRONT_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONNAVXLOGOFRONT_H_

#include <subsys/components/DragonNavX.h>
#include <AHRS.h>

class DragonNavXLogoFront : public DragonNavX
{

	public:
		DragonNavXLogoFront() = delete;
		DragonNavXLogoFront
		(
			DragonNavX::NAVX_PORT_TYPE		portType,
			int								portID,
			int								updateRate

		);
		virtual ~DragonNavXLogoFront() = default;

		float  GetPitch() override;
		float  GetRoll() override;
		float  GetYaw() override;
		float  GetCompassHeading() override;

		float  GetWorldLinearAccelX() override;
		float  GetWorldLinearAccelY() override;
		float  GetWorldLinearAccelZ() override;
		bool   IsMoving() override;
		bool   IsRotating() override;

		float  GetFusedHeading() override;

		float  GetQuaternionW() override;
		float  GetQuaternionX() override;
		float  GetQuaternionY() override;
		float  GetQuaternionZ() override;

		void   UpdateDisplacement
		(
			float accel_x_g,
			float accel_y_g,
			int update_rate_hz,
			bool is_moving
		) override;
		float  GetVelocityX() override;
		float  GetVelocityY() override;
		float  GetVelocityZ() override;
		float  GetDisplacementX() override;
		float  GetDisplacementY() override;
		float  GetDisplacementZ() override;
		double GetAngle() override;
		double GetRate() override;
		void   SetAngleAdjustment
		(
			double angle
		) override;
		double GetAngleAdjustment() override;

		float  GetRawGyroX() override;
		float  GetRawGyroY() override;
		float  GetRawGyroZ() override;
		float  GetRawAccelX() override;
		float  GetRawAccelY() override;
		float  GetRawAccelZ() override;
		float  GetRawMagX() override;
		float  GetRawMagY() override;
		float  GetRawMagZ() override;
};


#endif /* SRC_SUBSYS_COMPONENTS_DRAGONNAVXLOGOFRONT_H_ */
