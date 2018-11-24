/*
 * CyclePrimitives.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

#include <auton/CyclePrimitives.h>
#include <auton/PrimitiveFactory.h>
#include <auton/AutonSelector.h>
#include <auton/PrimitiveEnums.h>
#include<SmartDashboard/SmartDashboard.h>
#include <auton/PrimitiveParser.h>
#include <auton/PrimitiveParams.h>

#include <subsys/mechanisms/Lift.h>

CyclePrimitives::CyclePrimitives() :
		m_primParams(), m_currentPrimSlot(0), m_currentPrim(nullptr), m_primFactory(
				PrimitiveFactory::GetInstance()), m_doNothing(nullptr), m_autonSelector(
				new AutonSelector()) {
}

void CyclePrimitives::Init()
{
	m_currentPrimSlot = 0; //Reset current prim
	m_primParams.clear();
//	printf("selected auto file: %s \n", m_autonSelector->GetSelectedAutoFile().c_str());

//	printf("Breaks before doing the Parse XML Thing \n");

	m_primParams = PrimitiveParser::ParseXML( m_autonSelector->GetSelectedAutoFile() );

//	m_primParams = PrimitiveParser::ParseXML( "/home/lvuser/auton/shootertest.xml" );

//	printf("Breaks after doing the Parse XML Thing /n");

//	m_primParams = PrimitiveParser::ParseXML( "/home/lvuser/auton/LidarTest.xml" );

//	m_primParams = PrimitiveParser::ParseXML( "/home/lvuser/auton/Fourbar_Test.xml" );

//	m_primParams = PrimitiveParser::ParseXML( "/home/lvuser/auton/Center_PlaceLeftSwitch.xml" );

//	m_primParams = PrimitiveParser::ParseXML( "/home/lvuser/auton/LeftCorner_PlaceLeftScale.xml" );
//	m_primParams = PrimitiveParser::ParseXML( "/home/lvuser/auton/LeftCorner_PlaceRightScale.xml" );

//	m_primParams = PrimitiveParser::ParseXML( "/home/lvuser/auton/RightCorner_PlaceLeftScale.xml" );
//	m_primParams = PrimitiveParser::ParseXML( "/home/lvuser/auton/RightCorner_PlaceRightScale.xml" );

//	m_primParams = PrimitiveParser::ParseXML( "/home/lvuser/auton/TwoFourteen.xml" );

	if (!m_primParams.empty())
	{
//		printf(" Prim Params is empty \n");
		GetNextPrim();
	}

//	printf("Finished Cycle Prim Init");
}

void CyclePrimitives::RunCurrentPrimitive()
{
//	printf("Made it into RunCurrentPrimitive in Cycle Prims /n");

	if (m_currentPrim != nullptr)
	{
//            frc::SmartDashboard::PutNumber("Running Prim Number ", m_currentPrimSlot );
		m_currentPrim->Run();
		if (m_currentPrim->IsDone())
		{
			GetNextPrim();
		}
	}
	else
	{
//            frc::SmartDashboard::PutString("End of Prims ", "Do Nothing" );
		m_primParams.clear();	// clear the primitive params vector
		m_currentPrimSlot = 0;  //Reset current prim slot
		RunDoNothing();
	}

//	SmartDashboard::PutBoolean("IsDone", m_currentPrim->IsDone());
}

void CyclePrimitives::GetNextPrim()
{
	PrimitiveParams* currentPrimParam =
			(m_currentPrimSlot < (int) m_primParams.size()) ?
					m_primParams[m_currentPrimSlot] : nullptr;

	m_currentPrim =
			(currentPrimParam != nullptr) ?
					m_primFactory->GetIPrimitive(currentPrimParam) : nullptr;
	if (m_currentPrim != nullptr)
	{
		m_currentPrim->Init(currentPrimParam);
	}

	m_currentPrimSlot++;
}

void CyclePrimitives::RunDoNothing()
{
	if (m_doNothing == nullptr)
	{
		auto params = new PrimitiveParams( DO_NOTHING,          // identifier
		                                   100000.0,            // time
		                                   0.0,                 // distance
		                                   0.0,                 // target x location
		                                   0.0,                 // target y location
		                                   0.0,                 // heading
		                                   0.0,                 // start drive speed
		                                   0.0,                 // end drive speed
		                                   Lift::KEEP_SAME,     // lift height
		                                   false,
										   0.0
										   );             // grab cube
		m_doNothing = m_primFactory->GetIPrimitive(params);
		m_doNothing->Init(params);
	}
	m_doNothing->Run();
}
