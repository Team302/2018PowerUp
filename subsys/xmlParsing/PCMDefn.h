/*
 * PCMDefn.h
 *
 *  Created on: Jan 16, 2018
 *      Author: casti
 */

#ifndef PCMDEFN_H_
#define PCMDEFN_H_

// C++ Includes
#include <iostream>

// FRC includes
#include <Compressor.h>

// Team 302 includes
#include <subsys/xmlParsing/PCMDefn.h>

// Third Party Includes
#include <thirdParty/puxixml/pugixml.hpp>


using namespace frc;

class PCMDefn
{
    public:

        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a pcm XML element and create a Compressor* from
        //              its definition.
        // Returns:     Compressor*        compressor object (or nullptr if XML
        //                                 is ill-formed
        //-----------------------------------------------------------------------
        static Compressor* ParseXML
        (
            pugi::xml_node      PCMNode
        );
};

#endif /* PCMDEFN_H_ */
