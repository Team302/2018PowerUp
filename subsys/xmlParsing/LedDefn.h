/*
 * LedDfen.h
 *
 *  Created on: Jan 26, 2018
 *      Author: casti
 */

#ifndef SRC_SUBSYS_XMLPARSING_LEDDEFN_H_
#define SRC_SUBSYS_XMLPARSING_LEDDEFN_H_


// C++ Includes
#include <iostream>

// FRC includes

// Team 302 includes
#include <subsys/components/TrueColors.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>


#include <SmartDashboard/SmartDashboard.h>



class LedDefn
{
    public:

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
        static TrueColors* ParseXML
        (
                pugi::xml_node      LEDNode
        );
};

#endif /* SRC_SUBSYS_XMLPARSING_LEDDEFN_H_ */
