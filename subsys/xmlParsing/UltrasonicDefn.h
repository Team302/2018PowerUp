/*
 * UltrasonicDefn.h
 *
 *  Created on: Feb 6, 2018
 *      Author: team302
 */

#ifndef SRC_SUBSYS_XMLPARSING_ULTRASONICDEFN_H_
#define SRC_SUBSYS_XMLPARSING_ULTRASONICDEFN_H_

// C++ Includes
#include <iostream>

// FRC includes

// Team 302 includes
#include <subsys/components/DragonUltrasonic.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>


//============================================================================================
//  Class:          UltrasonicDefn
//  Description:    This class parses the ultrasonic node in the robot.xml file and creates
//                  a DragonUltrsonic*.
//============================================================================================
class UltrasonicDefn
{
    public:
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
        static DragonUltrasonic* ParseXML
        (
            pugi::xml_node UltraNode
        );
};
#endif /* SRC_SUBSYS_XMLPARSING_ULTRASONICDEFN_H_ */

