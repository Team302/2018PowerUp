/*
 * LedDfen.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: casti
 */

// C++ Includes
#include <iostream>

// FRC includes
#include <SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <factories/LEDFactory.h>
#include <subsys/components/TrueColors.h>
#include <subsys/xmlParsing/LedDefn.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>


//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a motor XML element and create a TrueColors object
//              from its definition.
//
//
//<!-- ====================================================
//     LEDs
//     ==================================================== -->
//<!ELEMENT led EMPTY>
//<!ATTLIST led
//          canId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
//                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 |
//                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
//                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 |
//                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
//                              60 | 61 | 62 ) "0"
//>
// Returns  TrueColors*         pointer to the LED controller object
//-----------------------------------------------------------------------
TrueColors* LedDefn::ParseXML
(
        pugi::xml_node      LEDNode
)
{
    // initialize output
    TrueColors* colors = nullptr;

    // initialize attributes
    int canID = 0; //led has only one attribute, canId


    bool hasError = false;

    // parse/validate xml
    for (pugi::xml_attribute attr = LEDNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp(attr.name(), "canId" ) == 0)
        {
            int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 63 )
            {
                canID = iVal;
            }
            else
            {
                printf( "==>> LedDefn::ParseXML invalid canId %d \n", iVal );
                hasError = true;
            }
        }
        else
        {
            printf( "==>> LedDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    // Create TrueColor object
    if ( !hasError )
    {
        colors = LEDFactory::GetFactory()->CreateLEDs( canID );
    }
    return colors;
}
