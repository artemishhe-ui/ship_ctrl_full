#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <sstream>
#include <iostream>
#include "GNSSData.h"


int parseNMEA_ROR(const std::string& sentence, Ship_state * storage)
{
    short error_index = -1;
    std::istringstream iss(sentence);

    std::string token;
    if (!(std::getline(iss, token, ',') && token.substr(3) == "ROR"))
    {
        LOG(FATAL) << "Token error in " << sentence;
        return error_index;
    }

    std::string Starboard_rudder_only;
    --error_index;
    if (!(std::getline(iss, Starboard_rudder_only, ',') && size(Starboard_rudder_only) != 0 && (Starboard_rudder_only.find_first_not_of("0123456789.") == Starboard_rudder_only.npos)))
    {
        LOG(WARNING) << "Starboard_rudder_only error in " << sentence;
        //std::cout << "Starboard_rudder_only is " << Starboard_rudder_only << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Starboard_rudder_only = stof(Starboard_rudder_only);
    

    std::string Status1;
    --error_index;
    if(!(std::getline(iss, Status1, ',') && (Status1 == "A" || Status1 == "V")))
    {
        LOG(WARNING) << "Status1 eroor in " << sentence;
        std::cout << "Status1 is " << Status1 << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "Status1 is " << Status1 << "   " << sentence << std::endl;
    storage->Status1 = Status1;
   


    std::string Port_rudder_order;
    --error_index;
    if (!(std::getline(iss, Port_rudder_order, ',') && size(Port_rudder_order) != 0 && (Port_rudder_order.find_first_not_of("0123456789.") == Port_rudder_order.npos)))
    {
        LOG(WARNING) << "Port_rudder_order error in " << sentence;
        //std::cout << "Port_rudder_order is " << Port_rudder_order << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Port_rudder_order = stof(Port_rudder_order);
    
    
    std::string Status2;
    --error_index;
    if(!(std::getline(iss, Status2, ',') && (Status2 == "A" || Status2 == "V")))
    {
        LOG(WARNING) << "Status2 eroor in " << sentence;
        std::cout << "Status2 is " << Status2 << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "Status2 is " << Status2 << "   " << sentence << std::endl;
    storage->Status2 = Status2;


    std::string Command_source_location;
    --error_index;
    if (!(std::getline(iss, Command_source_location, '*') && size(Command_source_location) != 0 && (Command_source_location.find_first_not_of("0123456789.") == Command_source_location.npos)))
    {
        LOG(WARNING) << "Command_source_location error in " << sentence;
        //std::cout << "Command_source_location is " << Command_source_location << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Command_source_location = Command_source_location;
    
    return 1;
}