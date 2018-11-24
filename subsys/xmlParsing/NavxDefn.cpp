/*
 * NavxDefn.cpp
 *
 */

// C++ Includes
#include <iostream>

// FRC includes
#include <SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <factories/DragonNavXFactory.h>
#include <subsys/xmlParsing/NavxDefn.h>
#include <subsys/components/DragonNavX.h>


// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>



using namespace frc;



//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a navX XML element and create a DragonNavX* from
//              its definition.
//
//<!-- ====================================================
//            enum NAVX_ORIENTATION
//            {
//                FLAT_LOGO_TOWARD_BACK,
//                FLAT_LOGO_TOWARD_FRONT,
//                FLAT_LOGO_TOWARD_LEFT_SIDE,
//                FLAT_LOGO_TOWARD_RIGHT_SIDE,
//                MAX_NAVX_TYPES
//            };
//
//            enum NAVX_PORT
//            {
//                SPI,
//                I2C,
//                SERIAL,
//                MAX_NAVX_PORTS
//            };
//
//    ==================================================== -->
//
//<!ELEMENT navx EMPTY>
//<!ATTLIST navx
//          orientation   ( 0 | 1 | 2 | 3 ) "0"
//          porttype      ( 0 | 1 | 2 ) "0"
//          portid        CDATA #REQUIRED
//          updaterate    CDATA #IMPLIED
//>
//
// Returns:     DragonNavX*        navX object (or nullptr if XML
//                                 is ill-formed
//-----------------------------------------------------------------------
DragonNavX* NavxDefn::ParseXML
(
    pugi::xml_node      NavxNode
)
{
    // initialize output
    DragonNavX* navx = nullptr;

    // initialize attributes to default values
    DragonNavXFactory::DRAGON_NAVX_ORIENTATION orientOpt = DragonNavXFactory::DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_BACK;
    DragonNavX::NAVX_PORT_TYPE porttype = DragonNavX::SPI;
    int portID = 0;
    int updaterated = 0;

    bool hasError = false;

    // parse/validate xml
    for (pugi::xml_attribute attr = NavxNode.first_attribute(); attr; attr = attr.next_attribute())
    {
         if ( strcmp( attr.name(), "orientation" ) == 0 )
         {
             int iVal = attr.as_int();
             switch ( iVal )
             {
                 case DragonNavXFactory::DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_BACK:
                     orientOpt = DragonNavXFactory::DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_BACK;
                     break;

                 case DragonNavXFactory::DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_FRONT:
                     orientOpt = DragonNavXFactory::DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_FRONT;
                     break;

                 case DragonNavXFactory::DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_LEFT_SIDE:
                     orientOpt = DragonNavXFactory::DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_LEFT_SIDE;
                     break;

                 case DragonNavXFactory::DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_RIGHT_SIDE:
                     orientOpt = DragonNavXFactory::DRAGONNAVX_ORIENT_FLAT_LOGO_TOWARD_RIGHT_SIDE;
                     break;

                 default:
                     printf( "==>> NavxDefn::ParseXML invalid navx orientation %d \n", iVal );
                     hasError = true;
                     break;
             }
         }
        else if ( strcmp( attr.name(), "porttype" ) == 0 )
        {
            int iVal = attr.as_int();
            switch ( iVal )
            {

                case DragonNavX::SPI:
                     porttype = DragonNavX::SPI;
                     break;

                 case DragonNavX::I2C:
                     porttype = DragonNavX::I2C;
                     break;

                 case DragonNavX::SERIAL:
                     porttype = DragonNavX::SERIAL;
                     break;

                 default:
                     printf( "==>> NavxDefn::ParseXML invalid navx orientation %d \n", iVal );
                     hasError = true;
                     break;
            }
        }
        else if ( strcmp( attr.name(), "portid" ) == 0 )
        {
            portID = attr.as_int();
        }
        else if ( strcmp( attr.name(), "updaterate" ) == 0 )
        {
            updaterated = attr.as_int();
        }
        else
        {
            printf( "==>> NavxDefn::ParseXML invalid attribute %s \n", attr.name() );
        }
    }

    // Create object
    if ( !hasError )
    {
        navx = DragonNavXFactory::GetNavXFactory()->CreateNavX( orientOpt, porttype, portID, updaterated );
    }
    return navx;
}

