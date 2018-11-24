/*
 * CompressorFactory.cpp
 */

#include <Compressor.h>
#include <factories/CompressorFactory.h>

using namespace frc;

CompressorFactory* CompressorFactory::m_factory = nullptr;
Compressor* CompressorFactory::m_pcm = nullptr;
DragonAnalogInput*  CompressorFactory::m_gauge = nullptr;

CompressorFactory* CompressorFactory::GetFactory()
{
	if (CompressorFactory::m_factory == nullptr)
	{
		CompressorFactory::m_factory = new CompressorFactory();
	}
	return CompressorFactory::m_factory;
}

Compressor* CompressorFactory::GetCompressor()
{
    return CompressorFactory::m_pcm;
}

DragonAnalogInput* CompressorFactory::GetPressureGauge()
{
    return CompressorFactory::m_gauge;
}
//=======================================================================================
// Method:  		CreateCompressor
// Description:		Create a compressor from the inputs
// Returns:         TrueColors*
//=======================================================================================
Compressor* CompressorFactory::CreateCompressor
(
        int         canID,                      // <I> - PCM CAN ID
        DragonAnalogInput*      pressureGauge   // <I> - pressure gauge
)
{
	CompressorFactory::m_pcm = new Compressor( canID );
	CompressorFactory::m_gauge = pressureGauge;

	return CompressorFactory::m_pcm;
}
