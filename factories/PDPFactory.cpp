/*
 * PDPFactory.cpp
 */

#include <factories/PDPFactory.h>
#include <PowerDistributionPanel.h>

using namespace frc;

PDPFactory* PDPFactory::m_factory = nullptr;
PowerDistributionPanel* PDPFactory::m_pdp = nullptr;

PDPFactory* PDPFactory::GetFactory()
{
	return PDPFactory::m_factory;
}

PowerDistributionPanel* PDPFactory::GetPDP()
{
	return PDPFactory::m_pdp;
}
//=======================================================================================
// Method:  		CreatePDP
// Description:		Create a PDP from the inputs
// Returns:         TrueColors*
//=======================================================================================
PowerDistributionPanel* PDPFactory::CreatePDP
(
	int			canID				// <I> - CANLight CAN ID
)
{
	PDPFactory::m_pdp = new PowerDistributionPanel( canID );

	return PDPFactory::m_pdp;
}

