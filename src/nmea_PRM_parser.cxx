#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <sstream>
#include <iostream>


struct PRM_container
{
    std::string Source;
    unsigned Engine_or_propeller_shaft;
    unsigned Speed;
    unsigned Propeller_pitch;
    std::string Status;
};

std::string generate_PRM()
{
    std::string Source = (rand() % 2) ? "E" : "V";
    std::string Engine_or_propeller_shaft = std::to_string(int(rand() % 100));
    std::string Speed = std::to_string(int(rand() % 100));
    std::string Propeller_pitch = std::to_string(int(rand() % 100));
    std::string Status = (rand() % 2) ? "A" : "V";
    std::string Comma = ",";

    return "$--PRM" + Comma + Source + Comma + Engine_or_propeller_shaft + Comma + Speed + Comma + Propeller_pitch + Comma + Status + 
    "*<CR><LF>";
}


std::string get_PRM(PRM_container container)
{
    std::string Source = container.Source;
    std::string Engine_or_propeller_shaft = std::to_string(container.Engine_or_propeller_shaft);
    std::string Speed = std::to_string(container.Speed);
    std::string Propeller_pitch = std::to_string(container.Propeller_pitch);
    std::string Status = container.Status
    std::string Comma = ",";

    return "$--PRM" + Comma + Source + Comma + Engine_or_propeller_shaft + Comma + Speed + Comma + Propeller_pitch + Comma + Status + 
    "*<CR><LF>";
}

int parseNMEA_PRM(const std::string& sentence, PRM_container storage)
{
    short error_index = -1;
    std::istringstream iss(sentence);

    std::string token;
    if (!(std::getline(iss, token, ',') && token.substr(3) == "PRM"))
    {
        LOG(FATAL) << "Token error in " << sentence;
        return error_index;
    }

    std::string Source;
    --error_index;
    if(!(std::getline(iss, Source, ',') && (Source == "S" || Source == "E")))
    {
        LOG(WARNING) << "Source eroor in " << sentence;
        std::cout << "Source is " << Source << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "Source is " << Source << "   " << sentence << std::endl;
    storage->Source = Source;
    


    std::string Engine_or_propeller_shaft;
    --error_index;
    if (!(std::getline(iss, Engine_or_propeller_shaft, ',') && size(Engine_or_propeller_shaft) != 0 && (Engine_or_propeller_shaft.find_first_not_of("0123456789.") == Engine_or_propeller_shaft.npos)))
    {
        LOG(WARNING) << "Engine_or_propeller_shaft error in " << sentence;
        //std::cout << "Engine_or_propeller_shaft is " << Engine_or_propeller_shaft << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Engine_or_propeller_shaft = stof(Engine_or_propeller_shaft);
    


    std::string Speed;
    --error_index;
    if (!(std::getline(iss, Speed, ',') && size(Speed) != 0 && (Speed.find_first_not_of("0123456789.") == Speed.npos)))
    {
        LOG(WARNING) << "Speed error in " << sentence;
        //std::cout << "Speed is " << Speed << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Speed = stof(Speed);
    


    std::string Propeller_pitch;
    --error_index;
    if (!(std::getline(iss, Propeller_pitch, ',') && size(Propeller_pitch) != 0 && (Propeller_pitch.find_first_not_of("0123456789.") == Propeller_pitch.npos)))
    {
        LOG(WARNING) << "Propeller_pitch error in " << sentence;
        //std::cout << "Propeller_pitch is " << Propeller_pitch << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Propeller_pitch = stof(Propeller_pitch);
    


    std::string Status;
    --error_index;
    if(!(std::getline(iss, Status, '*') && (Status == "A" || Status == "V")))
    {
        LOG(WARNING) << "Status eroor in " << sentence;
        std::cout << "Status is " << Status << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "Status is " << Status << "   " << sentence << std::endl;
    storage->Status = Status;


    return 1;
}
