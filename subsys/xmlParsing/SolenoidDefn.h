/*
 * SolenoidDefn.h
 *
 *  Created on: Jan 15, 2018
 *      Author: team302
 */

#ifndef SRC_SRC_SUBSYS_XMLPARSING_SOLENOIDDEFN_H_
#define SRC_SRC_SUBSYS_XMLPARSING_SOLENOIDDEFN_H_

// C++ Includes
#include <iostream>

// FRC includes
#include <SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <subsys/components/DragonSolenoid.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>

using namespace frc;

class SolenoidDefn
{
    public:
        SolenoidDefn() = delete;
        virtual ~SolenoidDefn() = delete;


        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a motor XML element and create a DragonTalon from
        //              its definition.
        // Returns:     DragonTalon*        motor controller (or nullptr if XML
        //                                  is ill-formed
        //
        //-----------------------------------------------------------------------
        static DragonSolenoid* ParseXML
        (
            pugi::xml_node      SolenoidNode
        );
};

#endif /* SRC_SRC_SUBSYS_XMLPARSING_SOLENOIDDEFN_H_ */
