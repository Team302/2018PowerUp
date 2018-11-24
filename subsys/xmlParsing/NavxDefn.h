/*
 * NavxDefn.h
 *
 */

#ifndef SRC_SUBSYS_XMLPARSING_NAVXDEFN_H_
#define SRC_SUBSYS_XMLPARSING_NAVXDEFN_H_

// C++ Includes
#include <iostream>

// FRC includes

// Team 302 includes
#include <subsys/xmlParsing/PCMDefn.h>

#include <subsys/components/DragonNavX.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>

using namespace frc;

class NavxDefn
{
    public:


    //-----------------------------------------------------------------------
    // Method:      ParseXML
    // Description: Parse a navX XML element and create a DragonNavX* from
    //              its definition.
    // Returns:     DragonNavX*        navX object (or nullptr if XML
    //                                 is ill-formed
    //-----------------------------------------------------------------------
    static DragonNavX* ParseXML
    (
        pugi::xml_node      NavXNode
    );

};

#endif /* SRC_SUBSYS_XMLPARSING_NAVXDEFN_H_ */
