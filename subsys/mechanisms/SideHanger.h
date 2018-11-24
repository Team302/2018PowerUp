/*
 * SideHanger.h
 *
 */

#ifndef SRC_SUBSYS_MECHANISMS_SIDEHANGER_H_
#define SRC_SUBSYS_MECHANISMS_SIDEHANGER_H_

#include <factories/MechanismFactory.h>
#include <interfaces/IMechanism.h>
#include <vector>

#include <subsys/components/DragonAnalogInput.h>
#include <subsys/components/DragonDigitalInput.h>
#include <subsys/components/DragonServo.h>
#include <subsys/components/DragonSolenoid.h>
#include <subsys/components/DragonTalon.h>


class SideHanger : public IMechanism
{
    public:
        enum SIDEBAR_MOVE_DIRECTION
        {
            CLOCKWISE,
            COUNTER_CLOCKWISE,
            STOP
        };
        SideHanger() = delete;
        SideHanger
        (
                IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
                const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
                const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
                const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
                const DragonAnalogInputVector&         analogInputs,       // <I> - Analog Inputs
                const DragonServoVector&            servos              // <I> - servos
        );
        virtual ~SideHanger();

        IMechanism::MECHANISM_TYPE GetType() const override;

        void RaiseBar
        (
            SIDEBAR_MOVE_DIRECTION  moveDirection               // <I> - Direction to move arm
        );
        void MoveBar(float speed);
        void LatchBar
        (
            bool    latch                                       // <I> - true = extend, false = retract
        );

        bool IsLatchExtended() const;

        void ReleaseTrident() const;

    private:
        DragonTalon*                m_spinMotor;
        DragonSolenoid*             m_latch;
//        DragonServo*                m_release;

        const float                 m_stopSpeed = 0.0;
        const float                 m_cwSpeed = 0.5;
        const float                 m_ccwSpeed = -0.5;

        const double                m_releaseAngle = 180.0;
};

#endif /* SRC_SUBSYS_MECHANISMS_SIDEHANGER_H_ */
