// --------------------------------------------------------------------------------------------
// AnalogInputDefn.cpp
// --------------------------------------------------------------------------------------------
//
// Description: Create an AnalogInput from an XML definition
//
// 	<!-- ====================================================
//		 analogInput type options
//	 	====================================================
//	 	enum ANALOG_SENSOR_TYPE
//	 	{
//	 		UNKNOWN_ANALOG_TYPE = -1,
//	 		ANALOG_GENERAL,
//	 		ANALOG_GYRO,
//	 		POTENTIOMETER,
//	 		PRESSURE_GAUGE,
//	 		MAX_ANALOG_TYPES
//	 	};
//	 	==================================================== -->
//	<!ELEMENT analogInput EMPTY>
//	<!ATTLIST analogInput
//  	      type              (  0 |  1 |  2 ) "0"
//      	  analogId          (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 ) "0"
//            voltageMin        CDATA "0.0"
//            voltageMax        CDATA "5.0"
//            outputMin         CDATA #REQUIRED
//            outputMax         CDATA #REQUIRED
//	>
//
// --------------------------------------------------------------------------------------------

// C++ includes

// FRC includes
#include <AnalogInput.h>
#include <SmartDashboard/SmartDashboard.h>

// Team302 includes
#include <subsys/components/DragonAnalogInput.h>
#include <subsys/xmlParsing/AnalogInputDefn.h>

// Third Party includes
#include <thirdParty/puxixml/pugixml.hpp>


using namespace frc;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a analogSensor XML element and create a DragonAnalogInput from
//              its definition.
// Returns:     DragonAnalogInput*      AnalogInput (or nullptr if XML
//                                  	is ill-formed
//-----------------------------------------------------------------------
DragonAnalogInput* AnalogInputDefn::ParseXML
(
    pugi::xml_node      motorNode
)
{
	DragonAnalogInput* sensor = nullptr;




	DragonAnalogInput::ANALOG_SENSOR_TYPE type = DragonAnalogInput::ANALOG_GENERAL;
	int 						analogID = 0;
    float						voltageMin = 0.0;
    float						voltageMax = 5.0;
    float 						outputMin  = 0.0;
    float						outputMax  = 1.0;

    bool hasError = false;

    // TODO:: Finish Parsing
    for (pugi::xml_attribute attr = motorNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "type" ) == 0 )
        {
        	int iVal = attr.as_int();
        	switch ( iVal )
        	{
        	case DragonAnalogInput::ANALOG_GENERAL:
        		type = DragonAnalogInput::ANALOG_GENERAL;
        		break;

        	case DragonAnalogInput::ANALOG_GYRO:
        		type = DragonAnalogInput::ANALOG_GYRO;
        		break;

        	case DragonAnalogInput::POTENTIOMETER:
        		type = DragonAnalogInput::POTENTIOMETER;
        		break;

        	case DragonAnalogInput::PRESSURE_GAUGE:
        		type = DragonAnalogInput::PRESSURE_GAUGE;
        		break;

        	default:
        		printf( "==>> AnalogInputDefn::ParseXML: invalid type %d \n", iVal );
        		break;

        	}
        }
        else if ( strcmp( attr.name(), "analogId" ) == 0 )
        {
        	analogID = attr.as_int();
        }
        else if ( strcmp( attr.name(), "voltageMin" ) == 0 )
        {
        	voltageMin = attr.as_float();
        }
        else if ( strcmp( attr.name(), "voltageMax" ) == 0 )
        {
        	voltageMax = attr.as_float();
        }
        else if ( strcmp( attr.name(), "outputMin" ) == 0 )
        {
        	outputMin = attr.as_float();
        }
        else if ( strcmp( attr.name(), "outputMax" ) == 0 )
        {
        	outputMax = attr.as_float();
        }
        else
        {
            printf( "AnalogInputDefn::ParseXML: invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    if ( !hasError )
    {
//        printf( "Creating AnalogInput \n");
//    	printf( "type: %d \n", type );
//    	printf( "analog ID: %d \n", analogID );
//    	printf( "min voltage: %g \n", voltageMin );
//    	printf( "max voltage: %g \n", voltageMax );
//    	printf( "min output value: %g \n", outputMin );
//    	printf( "max output value: %g \n", outputMax );

    	sensor = new DragonAnalogInput( type, analogID, voltageMin, voltageMax, outputMin, outputMax );

    }
    return sensor;
}
