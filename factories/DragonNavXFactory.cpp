/*
 * DragonNavXFactory.cpp
 */

#include <factories/DragonNavXFactory.h>
#include <subsys/components/DragonNavX.h>

#include <subsys/components/DragonNavXLogoBack.h>
#include <subsys/components/DragonNavXLogoFront.h>
#include <subsys/components/DragonNavXLogoLSide.h>
#include <subsys/components/DragonNavXLogoRSide.h>



DragonNavXFactory* DragonNavXFactory::m_navXFactory = nullptr;
DragonNavX* DragonNavXFactory::m_navX = nullptr;

DragonNavXFactory* DragonNavXFactory::GetNavXFactory()
{
	if ( DragonNavXFactory::m_navXFactory == nullptr )
	{
		DragonNavXFactory::m_navXFactory = new DragonNavXFactory();
	}
	return DragonNavXFactory::m_navXFactory;
}

DragonNavX* DragonNavXFactory::GetDragonNavX()
{
	return DragonNavXFactory::m_navX;
}

//=======================================================================================
// Method:  		CreateNavX
// Description:		Create a navx from the inputs
// Returns:         DragonNavX*
//=======================================================================================
DragonNavX* DragonNavXFactory::CreateNavX
(
	DRAGON_NAVX_ORIENTATION 		orient,				// <I> - Orientation
	DragonNavX::NAVX_PORT_TYPE		portType,
	int								portID,
	int								updateRate
)
{
	switch ( orient )
	{
		case DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_BACK:
			DragonNavXFactory::m_navX = new DragonNavXLogoBack( portType, portID, updateRate );
			break;

		case DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_FRONT:
			DragonNavXFactory::m_navX = new DragonNavXLogoFront( portType, portID, updateRate );
			break;

		case DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_LEFT_SIDE:
			DragonNavXFactory::m_navX = new DragonNavXLogoLSide( portType, portID, updateRate );
			break;

		case DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_RIGHT_SIDE:
			DragonNavXFactory::m_navX = new DragonNavXLogoRSide( portType, portID, updateRate );
			break;

		default:
			printf( "==>> DragonNavXFactory::CreateNavX Invalid orientation %d \n", orient );
			break;
	}
	return DragonNavXFactory::m_navX;

}
