/*
 * ArcadeDrive.h
 *
 *  Created on: Oct 29, 2017
 *      Author: jonah
 */

#ifndef SRC_TELEOP_DRIVE_ARCADEDRIVE_H_
#define SRC_TELEOP_DRIVE_ARCADEDRIVE_H_

#include <interfaces/IDrive.h>

/*
 * this class just directs the actions in OI to the actions in the chassis.
 */

class ArcadeDrive : public IDrive
{
public:
    ArcadeDrive();
	virtual ~ArcadeDrive() = default;

	//Drive the robot with input devices (controllers, joysticks, etc)
	void Drive() override;
    const char* GetIdentifier() const override;
};

#endif /* SRC_TELEOP_DRIVE_TELEOPDRIVE_H_ */
