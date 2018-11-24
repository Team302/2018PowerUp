/*
 * MotorDefn.h
 *
 */

#ifndef SRC_TEST_MOTORDEFN_H_
#define SRC_TEST_MOTORDEFN_H_

// C++ Includes

// FRC includes

// Team 302 includes
#include <subsys/components/DragonTalon.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>



class MotorDefn
{
    public:

        MotorDefn() = delete;
        virtual ~MotorDefn() = delete;


        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a motor XML element and create a DragonTalon from
        //              its definition.
        // Returns:     DragonTalon*        motor controller (or nullptr if XML
        //                                  is ill-formed
        //-----------------------------------------------------------------------
        static DragonTalon* ParseXML
        (
            pugi::xml_node      motorNode
        );
};


#endif /* SRC_TEST_MOTORDEFN_H_ */
