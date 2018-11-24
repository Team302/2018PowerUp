/*
 * TurnToCube.h
 *
 */

#ifndef SRC_AUTON_TURNTOCUBE_H_
#define SRC_AUTON_TURNTOCUBE_H_

#include <auton/PrimitiveParams.h>
#include <auton/TurnAngle.h>
#include <subsys/components/DragonLidar.h>

class TurnToCube: public TurnAngle
{
    public:
        TurnToCube();
        virtual ~TurnToCube() = default;

        void Init
        (
            PrimitiveParams* params
        ) override;
        void Run() override;
        bool IsDone() override;

    private:
        bool                    m_scanned;
        double                  m_minAngle;
        double                  m_minDist;
        DragonLidar*            m_lidar;

};

#endif /* SRC_AUTON_TURNTOCUBE_H_ */
