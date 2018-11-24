/*
 * LEDFactory.cpp
 */

#include <factories/LEDFactory.h>
#include <subsys/components/TrueColors.h>

LEDFactory* LEDFactory::m_factory = nullptr;
TrueColors* LEDFactory::m_leds = nullptr;

LEDFactory* LEDFactory::GetFactory()
{
	if (LEDFactory::m_factory == nullptr)
	{
		LEDFactory::m_factory = new LEDFactory();
	}
	return LEDFactory::m_factory;
}

TrueColors* LEDFactory::GetLEDs()
{
	return LEDFactory::m_leds;
}
//=======================================================================================
// Method:  		CreateLEDs
// Description:		Create a LEDs from the inputs
// Returns:         TrueColors*
//=======================================================================================
TrueColors* LEDFactory::CreateLEDs
(
	int			canID				// <I> - CANLight CAN ID
)
{
	LEDFactory::m_leds = new TrueColors( canID );

	return LEDFactory::m_leds;
}

