/*
 * DragonLidar.h
 *
 *  Created on: Feb 6, 2018
 *      Author: jonah
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONLIDAR_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONLIDAR_H_

//Includes
#include <WPILib.h>

/*
 * This class takes a LIDAR that is connected to a digital input on the roborio using PWM.
 * We measure the high pulse length and convert it to a distance in GetDistance()
 *
 * the trigger pin is just used to initialize the lidar. It shouldn't have to be called periodically.
 */

class DragonLidar
{
    public:
        enum LIDAR_USAGE
        {
            FORWARD_GRABBER,
            DOWNWARD_GRABBER,
            MAX_LIDAR_USAGES
        };
        DragonLidar
        (
            LIDAR_USAGE usage,
            int         inputPin,
            int         triggerPin
        );
        virtual ~DragonLidar();

        double GetDistance(); //In inches from the sensor
        LIDAR_USAGE GetUsage() const;

    private:
        LIDAR_USAGE     m_usage;
        Counter*        m_pulseWidthCounter;
        DigitalOutput*  m_trigger;
};

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONLIDAR_H_ */
