/*
 * CubeHandlerFactory.cpp
 */
#include <factories/CubeHandlerFactory.h>
#include <interfaces/ICubeHandler.h>
#include <teleop/controlMechanisms/CubeHandler.h>



CubeHandlerFactory* CubeHandlerFactory::m_factory = nullptr;

CubeHandlerFactory* CubeHandlerFactory::GetInstance()
{
	if ( CubeHandlerFactory::m_factory == nullptr )
	{
		CubeHandlerFactory::m_factory = new CubeHandlerFactory();
	}
	return CubeHandlerFactory::m_factory;
}

CubeHandlerFactory::CubeHandlerFactory() : m_handler ( nullptr ),
                                           m_floorHandler( nullptr ),
                                           m_switchHandler( nullptr ),
                                           m_scaleHandler( nullptr ),
                                           m_holdHandler( nullptr ),
                                           m_manualHandler( nullptr ),
                                           m_currentState( ICubeHandler::MANUAL_CONTROL )
{

}



CubeHandlerFactory::~CubeHandlerFactory()
{

}


ICubeHandler* CubeHandlerFactory::GetHandler
(
	ICubeHandler::CURRENT_CUBEHANDLER_STATE state
)
{
	ICubeHandler* mech = nullptr;

	switch ( state )
	{
	    case ICubeHandler::MOVE_TO_FLOOR_POS:
	        mech = new CubeToFloor();
	        break;

	    case ICubeHandler::MOVE_TO_SWITCH_POS:
	        mech = new CubeToSwitch();
	        break;

	    case ICubeHandler::MOVE_TO_SCALE_POS:
	        mech = new CubeToScale();
	        break;

	    case ICubeHandler::HOLD_POS:
	        mech = new CubeHoldPos();
	        break;

	    case ICubeHandler::MANUAL_CONTROL:
	        mech = new CubeManualControl();
	        break;

		default:
		break;
	}

	return mech;
}

