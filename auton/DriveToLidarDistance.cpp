/*
 * DriveToLidarDistance.cpp
 *
 */

#include <auton/DriveDistance.h>
#include <auton/DriveToLidarDistance.h>
#include <auton/PrimitiveParams.h>
#include <factories/LidarFactory.h>

DriveToLidarDistance::DriveToLidarDistance() :
	m_lidar( nullptr ),
	m_underDistanceCounts( 0 ),
	m_minTimeToRun( 0 )
{
    LidarFactory* factory = LidarFactory::GetLidarFactory();
    if ( factory != nullptr )
    {
        m_lidar = factory->GetLidar( DragonLidar::FORWARD_GRABBER );
    }
}


void DriveToLidarDistance::Init
(
    PrimitiveParams* params
)
{
    if ( m_lidar != nullptr )
    {
        params->SetDistance( m_lidar->GetDistance() );
    }
    else
    {
    	printf("heyyy that lidar is nullptr \n");
    }

	m_minTimeToRun = 0.3;
    m_underDistanceCounts = 0;

    DriveDistance::Init( params );
}

void DriveToLidarDistance::Run()
{
	DriveDistance::Run();
	if (m_minTimeToRun <= 0) {
		if ( m_lidar->GetDistance() <= MIN_CUBE_DISTANCE ) {
			m_underDistanceCounts++;
		}
	}

	m_minTimeToRun -= IPrimitive::LOOP_LENGTH;
}

bool DriveToLidarDistance::IsDone()
{
	bool done = m_underDistanceCounts >= UNDER_DISTANCE_COUNT_THRESHOLD;

	return ( DriveDistance::IsDone() || done );
}
