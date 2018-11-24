/*
 * PCMDefn.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: casti
 */

// C++ Includes
#include <iostream>

// FRC includes
#include <Compressor.h>
#include <SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <factories/CompressorFactory.h>
#include <subsys/components/DragonAnalogInput.h>
#include <subsys/xmlParsing/AnalogInputDefn.h>
#include <subsys/xmlParsing/PCMDefn.h>


// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>


using namespace frc;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a pcm XML element and create a Compressor* from
//              its definition.
//
//<!-- ====================================================
//     PCM (compressor)
//     ==================================================== -->
//<!ELEMENT pcm (analogInput?)>
//<!ATTLIST pcm
//          canId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
//                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 |
//                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
//                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 |
//                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
//                              60 | 61 | 62 ) "0"
//>
//
// Returns:     Compressor*        compressor object (or nullptr if XML
//                                 is ill-formed
//-----------------------------------------------------------------------
Compressor* PCMDefn::ParseXML
(
    pugi::xml_node      PCMNode
)
{
    // initialize output
    Compressor* compress = nullptr;

    // initialize attributes to default values
    int canID = 0;

    DragonAnalogInput* pressureGauge = nullptr;

    bool hasError = false;

    // parse/validate XML
    for (pugi::xml_attribute attr = PCMNode.first_attribute(); attr; attr = attr.next_attribute())
    {
         if ( strcmp( attr.name(), "canId" ) == 0 )
         {
            int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 63 )
            {
                canID = iVal;
            }
            else
            {
                printf( "==>> PCMDefn::ParseXML invalid canId %d \n", iVal );
                hasError = true;
            }
         }
         else
         {
            printf( "==>> PCMDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
         }
    }

    //--------------------------------------------------------------------------------------------
    // Process child element nodes
    //--------------------------------------------------------------------------------------------
    for (pugi::xml_node child = PCMNode.first_child(); child; child = child.next_sibling())
    {
        if ( strcmp( child.name(), "analogInput") == 0 )
        {
            pressureGauge = AnalogInputDefn::ParseXML( child );
        }
        else
        {
            printf( "==>> pcm unknown child %s \n", child.name() );
        }
    }
    // Create compressor
    if ( !hasError )
    {
        compress = CompressorFactory::GetFactory()->CreateCompressor( canID, pressureGauge );
    }
    return compress;

}
