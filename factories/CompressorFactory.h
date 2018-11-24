/*
 * CompressorFactory.h
 */

#ifndef SRC_FACTORIES_COMPRESSORFACTORY_H_
#define SRC_FACTORIES_COMPRESSORFACTORY_H_


#include <Compressor.h>

#include <subsys/components/DragonAnalogInput.h>

using namespace frc;

class CompressorFactory
{
	public:
		static CompressorFactory* GetFactory();

        static Compressor* GetCompressor();

        static DragonAnalogInput* GetPressureGauge();

		//=======================================================================================
		// Method:  		CreateCompressor
		// Description:		Create a PDP from inputs
		// Returns:         Void
		//=======================================================================================
		Compressor* CreateCompressor
		(
			int			canID,      				// <I> - PCM CAN ID
			DragonAnalogInput*      pressureGauge   // <I> - pressure gauge
		);

	private:
		CompressorFactory() = default;
		virtual ~CompressorFactory() = default;

		static CompressorFactory*		  	m_factory;
		static Compressor*      			m_pcm;
		static DragonAnalogInput*           m_gauge;


};

#endif /* SRC_FACTORIES_COMPRESSORFACTORY_H_ */
