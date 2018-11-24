/*
 * DragonNavXFactory.h
 */

#ifndef SRC_FACTORIES_DRAGONNAVXFACTORY_H_
#define SRC_FACTORIES_DRAGONNAVXFACTORY_H_

#include <subsys/components/DragonNavX.h>


class DragonNavXFactory
{
	public:

		enum DRAGON_NAVX_ORIENTATION
		{
			DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_BACK,
			DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_FRONT,
			DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_LEFT_SIDE,
			DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_RIGHT_SIDE,
			MAX_DRAGONNAVX_ORIENTATIONS
		};


			static DragonNavXFactory* GetNavXFactory();
			static DragonNavX* GetDragonNavX();

			//=======================================================================================
			// Method:  		CreateNavX
			// Description:		Create a navx from the inputs
			// Returns:         Void
			//=======================================================================================
			DragonNavX* CreateNavX
			(
				DRAGON_NAVX_ORIENTATION 		orient,				// <I> - Orientation
				DragonNavX::NAVX_PORT_TYPE		portType,
				int								portID,
				int								updateRate
			);



	private:
		DragonNavXFactory() = default;
		~DragonNavXFactory() = default;

		static DragonNavXFactory*	m_navXFactory;
		static DragonNavX*			m_navX;



};

#endif /* SRC_FACTORIES_DRAGONNAVXFACTORY_H_ */
