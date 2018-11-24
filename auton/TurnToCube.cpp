/*
 * TurnToCube.cpp
 *
 */

#include <auton/PrimitiveParams.h>
#include <auton/TurnAngle.h>
#include <auton/TurnToCube.h>
#include <factories/ChassisFactory.h>
#include <factories/LidarFactory.h>

TurnToCube::TurnToCube() : m_scanned( false ),
                           m_minAngle( 360.0 ),     // complete revolution
                           m_minDist( 648.0 ),      // 54 feet * 12 inches per foot
                           m_lidar( nullptr )
{
    LidarFactory* factory = LidarFactory::GetLidarFactory();
    if ( factory != nullptr )
    {
        m_lidar = factory->GetLidar( DragonLidar::FORWARD_GRABBER );
    }
}


void TurnToCube::Init(PrimitiveParams* params)
{
    TurnAngle::Init( params );
    m_scanned  = false;
    m_minAngle = 360.0;
    if ( m_lidar != nullptr )
    {
        m_minDist = m_lidar->GetDistance();
    }
}

void TurnToCube::Run()
{
    TurnAngle::Run();
    if ( m_lidar != nullptr )
    {
        double currDist = m_lidar->GetDistance();
        if ( currDist < m_minDist )
        {
            m_minDist = currDist;
            m_minAngle = ChassisFactory::GetChassisFactory()->GetIChassis()->GetHeading();
        }
    }
}

bool TurnToCube::IsDone()
{
    bool done = TurnAngle::IsDone();
    if ( done && !m_scanned )
    {
        done = false;
        m_scanned = true;
//        TurnAngle::SetTargetAngle( m_minAngle );
        //TODO: figure out a different way to do this
    }
    return done;
}


