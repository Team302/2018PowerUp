/*
 * ChassisFactory.cpp
 *
 */
#include <factories/ChassisFactory.h>
#include <interfaces/IChassis.h>
//#include <subsys/chassis/MecanumChassis.h>
//#include <subsys/chassis/MegaMecanumChassis.h>
#include <vector>

#include <subsys/components/DragonTalon.h>

#include <subsys/chassis/RegularChassis.h>


ChassisFactory* ChassisFactory::m_chassisFactory = nullptr;
IChassis* ChassisFactory::m_chassis = nullptr;

ChassisFactory* ChassisFactory::GetChassisFactory()
{
	if ( ChassisFactory::m_chassisFactory == nullptr )
	{
		ChassisFactory::m_chassisFactory = new ChassisFactory();
	}
	return ChassisFactory::m_chassisFactory;
}

IChassis* ChassisFactory::GetIChassis()
{
	return ChassisFactory::m_chassis;
}

//=======================================================================================
// Method:  		CreateChassis
// Description:		Create a chassis from the inputs
// Returns:         Void
//=======================================================================================
IChassis* ChassisFactory::CreateChassis
(
	CHASSIS_TYPE     			type,				// <I> - Chassis Type
	float 						wheelDiameter,		// <I> - Diameter of the wheel
    float 						wheelBase,			// <I> - Front-Back distance between wheel centers
	float 						track,				// <I> - Left-Right distance between wheels (same axle)
	std::vector<DragonTalon*> 	motorControllers	// <I> - Motor Controllers
)
{
	switch ( type )
	{
		case TANK_CHASSIS:
//			printf( "==>> creating regular chassis \n");
			ChassisFactory::m_chassis = new RegularChassis( wheelDiameter, wheelBase, track, motorControllers );
			break;

//		case MECANUM_CHASSIS:
//			if ( motorControllers.size() == 4 )
//			{
//				ChassisFactory::m_chassis = new MecanumChassis( wheelDiameter, wheelBase, track, motorControllers );
//			}
//			else if ( motorControllers.size() == 8 )
//			{
//				ChassisFactory::m_chassis = new MegaMecanumChassis( wheelDiameter, wheelBase, track, motorControllers );
//			}
//			else
//			{
//				printf( "==>> ChassisFactory::CreateChassis unsupported number of mecanum wheels %d \n", motorControllers.size() );
//			}
//			break;

		default:
			printf( "==>> ChassisFactory::CreateChassis Invalid type %d \n", type );
			break;
	}
	return ChassisFactory::m_chassis;

}


