/*
 * RobotDefn.cpp
 *
 */

// C++ Includes
#include <iostream>

// FRC includes
#include <SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <subsys/xmlParsing/RobotDefn.h>
#include <subsys/xmlParsing/CameraDefn.h>
#include <subsys/xmlParsing/ChassisDefn.h>
#include <subsys/xmlParsing/LedDefn.h>
#include <subsys/xmlParsing/LidarDefn.h>
#include <subsys/xmlParsing/MechanismDefn.h>
#include <subsys/xmlParsing/NavxDefn.h>
#include <subsys/xmlParsing/PCMDefn.h>
#include <subsys/xmlParsing/PDPDefn.h>
#include <subsys/xmlParsing/PigeonDefn.h>

#include <subsys/components/TrueColors.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>


using namespace frc;
//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a robot.xml file
// Returns:     void
//-----------------------------------------------------------------------
void RobotDefn::ParseXML()
{
    // set the file to parse
    const char* filename = "/home/lvuser/config/robot.xml";

    // load the xml file into memory (parse it)
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file( filename );

    // if it is good
    if ( result )
    {
        printf( "XML file [ %s ] parsed without errors \n ", filename );

        // get the root node <robot>
        pugi::xml_node parent = doc.root();
        for (pugi::xml_node node = parent.first_child(); node; node = node.next_sibling())
        {
            // loop through the direct children of <robot> and call the appropriate parser
            for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling())
            {
                if ( strcmp( child.name(), "chassis") == 0 )
                {
                    ChassisDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "mechanism") == 0 )
                {
                    MechanismDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "pcm") == 0 )
                {
                    PCMDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "pdp") == 0 )
                {
                    PDPDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "led") == 0 )
                {
                    LedDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "navx") == 0 )
                {
                    NavxDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "pigeon") == 0 )
                {
                    PigeonDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "lidar") == 0 )
                {
                    LidarDefn::ParseXML( child );
                }
                else if ( strcmp( child.name(), "camera") == 0 )
                {
                    CameraDefn::ParseXML( child );
                }
                else
                {
                    printf( "==>>RobotDefn::ParseXML unknown robot child %s \n", child.name() );
                }
            }
        }
    }
    else
    {
        std::cout << "XML [" << filename << "] parsed with errors, attr value: [" << doc.child("prototype").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (filename + result.offset) << "]\n\n";
    }
}
