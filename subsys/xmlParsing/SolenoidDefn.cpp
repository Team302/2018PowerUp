/*
 * SolenoidDefn.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: team302
 */

#include <subsys/xmlParsing/SolenoidDefn.h>
#include <subsys/components/DragonSolenoid.h>

// C++ Includes
#include <iostream>

// FRC includes
#include <SmartDashboard/SmartDashboard.h>

// Team 302 includes

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>

using namespace frc;

//-----------------------------------------------------------------------
// Method:      ParseXML 39769
// Description: Parse a solenoid XML element and create a DragonSolenoid from
//              its definition.
//
//
//<!-- ====================================================
//     solenoid usage options -->
//     ====================================================
//        enum DRAGON_SOLENOID_USAGE
//        {
//            CONTROL_4BAR,
//            GRABBER_CLUTCH,
//            GRABBER_POSITION,
//            SIDEHANGER_LATCH
//        };
//     ==================================================== -->
//<!ELEMENT solenoid EMPTY>
//<!ATTLIST solenoid
//          usage             (  0 |  1 | 2 ) "0"
//          pcmId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
//                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 |
//                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
//                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 |
//                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
//                              60 | 61 | 62 ) "0"
//          channel           (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 ) "0"
//          reversed          ( true | false ) "false"
//>
//
//
//
// Returns:     DragonSolenoid*     solenoid (or nullptr if XML
//                                  is ill-formed
//-----------------------------------------------------------------------
DragonSolenoid* SolenoidDefn::ParseXML
(
    pugi::xml_node      SolenoidNode
)
{
    // initialize output
    DragonSolenoid* sol = nullptr;

    // initialize attributes to default values
    DragonSolenoid::DRAGON_SOLENOID_USAGE usage    = DragonSolenoid::CONTROL_4BAR;
    int  pcmID    = 0;
    int  channel  = 0;
    bool reversed = false;

    bool hasError = false;

    // parse/validate xml
    for (pugi::xml_attribute attr = SolenoidNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
            int iVal = attr.as_int();
            switch ( iVal )
            {
                case DragonSolenoid::CONTROL_4BAR:
                    usage = DragonSolenoid::CONTROL_4BAR;
                    break;

                case DragonSolenoid::GRABBER_CLUTCH:
                    usage = DragonSolenoid::GRABBER_CLUTCH;
                    break;

                case DragonSolenoid::GRABBER_POSITION:
                    usage = DragonSolenoid::GRABBER_POSITION;
                    break;

                case DragonSolenoid::SIDEHANGER_LATCH:
                    usage = DragonSolenoid::SIDEHANGER_LATCH;
                    break;

                default:
                    printf( "==>> SolenoidDefn::ParseXML invalid usage option %d \n", iVal );
                    hasError = true;
                    break;
            }
        }

        else if ( strcmp( attr.name(), "pcmId" ) == 0 )
        {
            int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 63 )
            {
                pcmID = iVal;
            }
            else
            {
                printf( "==>> SolenoidDefn::ParseXML invalid pcmID %d \n", iVal );
                hasError = true;
            }
        }
        else if ( strcmp( attr.name(), "channel" ) == 0 )
        {
            int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 8 )
            {
                channel = iVal;
            }
            else
            {
                printf( "==>> SolenoidDefn::ParseXML invalid channel %d \n", iVal );
                hasError = true;
            }
        }
        else if ( strcmp( attr.name(), "reversed" ) == 0 )
        {
            reversed = attr.as_bool();
        }
        else
        {
            printf( "==>> SolenoidDefn::ParseXML unknown attribute %s \n ", attr.name() );
        }
    }

    // Create the object
    if ( !hasError )
    {
        sol = new DragonSolenoid( usage, pcmID, channel, reversed );
    }

    return sol;
}



