/*
 * DriveToLidarDistance.h
  *  Created on: Feb 20, 2018
 *      Author: Austin
 */

#ifndef SRC_AUTON_DRIVETOLIDARDISTANCE_H_
#define SRC_AUTON_DRIVETOLIDARDISTANCE_H_

#include <auton/DriveDistance.h>
#include <auton/PrimitiveParams.h>
#include <subsys/components/DragonLidar.h>

class DriveToLidarDistance: public DriveDistance
{
    public:
        DriveToLidarDistance();
        virtual ~DriveToLidarDistance() = default;

        bool IsDone() override;
        void Run() override;
        void Init(PrimitiveParams* params) override;

    private:
    // Objects
    DragonLidar*            m_lidar;

    // Vars
    int m_underDistanceCounts;						// # of counts that the robot has a cube
    float m_minTimeToRun;								// Forces the drive to run for at least this long

    // Consts
    const float MIN_CUBE_DISTANCE = 3.0;				// Min Distance in inches to a cube to be counted as in the robot
    const int UNDER_DISTANCE_COUNT_THRESHOLD = 4;			// # of counts to determine we have a cube.... or a wall

};

#endif /* SRC_AUTON_DRIVETOLIDARDISTANCE_H_ */
