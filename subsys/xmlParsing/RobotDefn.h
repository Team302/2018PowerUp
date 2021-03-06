/*
 * RobotDefn.h
 *
 */

#ifndef SRC_SUBSYS_XMLPARSING_ROBOTDEFN_H_
#define SRC_SUBSYS_XMLPARSING_ROBOTDEFN_H_

// C++ Includes

// FRC includes

// Team 302 includes
#include <subsys/components/TrueColors.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>


using namespace frc;

class RobotDefn
{
    public:
        RobotDefn() = delete;
        virtual ~RobotDefn() = delete;


        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a robot.xml file
        // Returns:     void
        //-----------------------------------------------------------------------
        static void ParseXML();

};

#endif /* SRC_SUBSYS_XMLPARSING_ROBOTDEFN_H_ */
