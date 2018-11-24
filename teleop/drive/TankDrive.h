/*
 * TankDrive.h
 *
 *  Created on: Jan 27, 2018
 *      Author: casti
 */

#ifndef SRC_TELEOP_DRIVE_TANKDRIVE_H_
#define SRC_TELEOP_DRIVE_TANKDRIVE_H_

#include <interfaces/IDrive.h>

class TankDrive : public IDrive
{
public:
	TankDrive();
	virtual ~TankDrive() = default;

	void Drive()  override;
    const char* GetIdentifier() const override;
};

#endif /* SRC_TELEOP_DRIVE_TANKDRIVE_H_ */
