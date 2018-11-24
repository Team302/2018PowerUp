/*
 * UltrasonicDefn.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: team302
 */


// C++ Includes
#include <iostream>

// FRC includes

// Team 302 includes
#include <subsys/xmlParsing/UltrasonicDefn.h>
#include <subsys/components/DragonUltrasonic.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>

//-----------------------------------------------------------------------------------
// Method:      ParseXML
// Description: Parses an ultrsonic element and creates a DragonUltrasonic* object.
//
//               <!ELEMENT ultrasonic EMPTY>
//               <!ATTLIST ultrasonic
//                         type              (  0 |  1 |  2 ) "0"
//                         channel           (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 ) "0"
//                >
//-----------------------------------------------------------------------------------
DragonUltrasonic* UltrasonicDefn::ParseXML
(
    pugi::xml_node          UltraNode
)
{
    // initialize the output
    DragonUltrasonic* ultrasonic = nullptr;

    // initialize the attributes to default values
    DragonUltrasonic::ULTRASONIC_USAGE usage = DragonUltrasonic::LEFT_SIDE_DISTANCE;
    int channel = 0;


    bool hasError = false;

    // Parse the XML
    for (pugi::xml_attribute attr = UltraNode.first_attribute();attr;attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(),  "usage" ) == 0)
        {
            int iVal = attr.as_int();
            switch ( iVal )
            {
                case DragonUltrasonic::LEFT_SIDE_DISTANCE:
                    usage = DragonUltrasonic::LEFT_SIDE_DISTANCE;
                    break;

                case DragonUltrasonic::RIGHT_SIDE_DISTANCE:
                    usage = DragonUltrasonic::RIGHT_SIDE_DISTANCE;
                    break;

                default:
                    printf( "==>> UltrasonicDefn::ParseXML unknown ultrasonic type %d \n", iVal );
                    hasError = true;
                    break;

            }
        }
        else if ( strcmp( attr.name(),  "channel" ) == 0)
        {
            int iVal = attr.as_int();
            if ( iVal >= 0 && iVal <= 7 )
            {
                channel = iVal;
            }
            else
            {
                printf( "==>> UltrasonicDefn::ParseXML  invalid channel %d \n", iVal );
                hasError = true;
            }
        }
    }

    // if there isn't an error create the DragonUltrasonic object
    if ( !hasError )
    {
        //TODO use a factory
        ultrasonic = new DragonUltrasonic( usage, channel );

    }
    return ultrasonic;
}


