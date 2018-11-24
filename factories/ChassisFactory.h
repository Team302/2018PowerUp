/*
 * ChassisFactory.h
 *
 *  Created on: Jan 15, 2018
 */

#ifndef SRC_FACTORIES_CHASSISFACTORY_H_
#define SRC_FACTORIES_CHASSISFACTORY_H_

#include <interfaces/IChassis.h>
#include <vector>

#include <subsys/components/DragonTalon.h>

class ChassisFactory
{

		public:
			enum CHASSIS_TYPE
			{
				UNKNOWN_CHASSIS = -1,
				TANK_CHASSIS,
				MECANUM_CHASSIS,
				MAX_CHASSIS_TYPES
			};
			static ChassisFactory* GetChassisFactory();

			static IChassis* GetIChassis();

			//=======================================================================================
			// Method:  		CreateChassis
			// Description:		Create a chassis from the inputs
			// Returns:         Void
			//=======================================================================================
			IChassis* CreateChassis
			(
				CHASSIS_TYPE     			type,				// <I> - Chassis Type
				float 						wheelDiameter,		// <I> - Diameter of the wheel
			    float 						wheelBase,			// <I> - Front-Back distance between wheel centers
				float 						track,				// <I> - Left-Right distance between wheels (same axle)
				std::vector<DragonTalon*> 	motorControllers	// <I> - Motor Controllers
			);



		private:
			ChassisFactory() = default;
			~ChassisFactory() = default;

			static ChassisFactory*	m_chassisFactory;
			static IChassis*        m_chassis;

};

#endif /* SRC_FACTORIES_CHASSISFACTORY_H_ */
