/*
 * PDPFactory.h
 */

#ifndef SRC_FACTORIES_PDPFACTORY_H_
#define SRC_FACTORIES_PDPFACTORY_H_


#include <PowerDistributionPanel.h>

using namespace frc;

class PDPFactory
{
	public:
		static PDPFactory* GetFactory();

		static PowerDistributionPanel* GetPDP();

		//=======================================================================================
		// Method:  		CreatePDP
		// Description:		Create a PDP from inputs
		// Returns:         Void
		//=======================================================================================
		PowerDistributionPanel* CreatePDP
		(
			int			canID				// <I> - PDP CAN ID
		);

	private:
		PDPFactory() = delete;
		virtual ~PDPFactory() = default;

		static PDPFactory*		  			m_factory;
		static PowerDistributionPanel*      m_pdp;

};


#endif /* SRC_FACTORIES_PDPFACTORY_H_ */
