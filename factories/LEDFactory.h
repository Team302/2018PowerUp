/*
 * LEDFactory.h
 */

#ifndef SRC_FACTORIES_LEDFACTORY_H_
#define SRC_FACTORIES_LEDFACTORY_H_

#include <subsys/components/TrueColors.h>

class LEDFactory
{
	public:
		static LEDFactory* GetFactory();

		static TrueColors* GetLEDs();

		//=======================================================================================
		// Method:  		CreateLEDs
		// Description:		Create a LEDs from inputs
		// Returns:         Void
		//=======================================================================================
		TrueColors* CreateLEDs
		(
			int			canID				// <I> - CANLight CAN ID
		);

	private:
		LEDFactory() = default;
		virtual ~LEDFactory() = default;

		static LEDFactory*		  m_factory;
		static TrueColors*        m_leds;

};

#endif /* SRC_FACTORIES_LEDFACTORY_H_ */
