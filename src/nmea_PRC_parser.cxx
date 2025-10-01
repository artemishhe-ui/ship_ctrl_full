#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <sstream>
#include <iostream>

struct PRC_container
(
    unsigned Lever_demand_position;
    std::string Lever_demand_status;
    unsigned PRM_demand_value;
    std::string PRM_mode_indicator;
    unsigned Pitch_demand_value;
    std::string Pitch_mode_indicator;
    std::string Operating_location_indicator;
    int Number_of_engine_or_propeller_shaft;
);

std::string generate_prc()
{
    std::string ret_str="$--PRC,";
    ret_str.reserve(37*sizeof(char));
    int help = rand() % 3;
    ret_str+= std::to_string(rand() % 200 - 100); //Lever_demand_position
    ret_str+= ',';
    ret_str+= (rand() % 2) ? 'A' : 'V'; //Lever_demand_status
    ret_str+= ',';
    ret_str+=  std::to_string(rand() % 100);   //PRM_demand_value
    ret_str+= ',';
    help = rand() % 3;
    ret_str+= (help == 0) ? 'V' : ((help == 1) ? 'R' : 'P'); //PRM_mode_indicator
    ret_str+= ',';
    ret_str+= std::to_string(rand() % 100);  //Pitch_demand_value
    ret_str+= ',';
    help = rand() % 3;
    ret_str+= (help == 0) ? 'V' : ((help == 1) ? 'D' : 'P');;  //Pitch_mode_indicator
    ret_str+= ',';
    help = rand() % 6;
    ret_str+= (help == 0) ? 'B' : ((help == 1) ? 'P' : ((help == 2) ? 'S' : ((help == 3) ? 'C' : ((help == 4) ? 'E' : 'W')))); //Operating_location_indicator
    ret_str+= ',';
    ret_str+= std::to_string(rand() % 100); //Number_of_engine_or_propeller_shaft
    ret_str+= "*<CR><LF>";

    return ret_str;
}

td::string get_prc(const PRC_container& container)
{
    std::string ret_str="$--PRC,";
    ret_str.reserve(37*sizeof(char));
    ret_str+= std::to_string(container.Lever_demand_position);
    ret_str+= ',';
    ret_str+= container.Lever_demand_status;
    ret_str+= ',';
    ret_str+=  std::to_string(container.PRM_demand_value);
    ret_str+= ',';
    ret_str+= container.PRM_mode_indicator;
    ret_str+= ',';
    ret_str+= std::to_string(container.Pitch_demand_value);
    ret_str+= ',';
    ret_str+= container.Pitch_mode_indicator;
    ret_str+= ',';
    ret_str+= container.Operating_location_indicator;
    ret_str+= ',';
    ret_str+= std::to_string(container.Number_of_engine_or_propeller_shaft); 
    ret_str+="*<CR><LF>"; 

    return ret_str;
}

int parseNMEA_PRC(const std::string& sentence, PRC_container* storage)
{
    short error_index = -1;
    std::istringstream iss(sentence);

    std::string token;
    if (!(std::getline(iss, token, ',') && token.substr(3) == "PRC"))
    {
        LOG(FATAL) << "Token error in " << sentence;
        return error_index;
    }

    std::string Lever_demand_position;
    --error_index;
    if (!(std::getline(iss, Lever_demand_position, ',') && size(Lever_demand_position) != 0 && (Lever_demand_position.find_first_not_of("0123456789.") == Lever_demand_position.npos)))
    {
        LOG(WARNING) << "Lever_demand_position error in " << sentence;
        //std::cout << "Lever_demand_position is " << Lever_demand_position << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Lever_demand_position = stof(Lever_demand_position);


    std::string Lever_demand_status;
    --error_index;
    if(!(std::getline(iss, Lever_demand_status, ',') && (Lever_demand_status == "A" || Lever_demand_status == "V")))
    {
        LOG(WARNING) << "Lever_demand_status eroor in " << sentence;
        std::cout << "Lever_demand_status is " << Lever_demand_status << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "Lever_demand_status is " << Lever_demand_status << "   " << sentence << std::endl;
    storage->Lever_demand_status = Lever_demand_status;


    std::string PRM_demand_value;
    --error_index;
    if (!(std::getline(iss, PRM_demand_value, ',') && size(PRM_demand_value) != 0 && (PRM_demand_value.find_first_not_of("0123456789.") == PRM_demand_value.npos)))
    {
        LOG(WARNING) << "PRM_demand_value error in " << sentence;
        //std::cout << "PRM_demand_value is " << PRM_demand_value << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->PRM_demand_value = stof(PRM_demand_value);



    std::string PRM_mode_indicator;
    --error_index;
    if(!(std::getline(iss, PRM_mode_indicator, ',') && (PRM_mode_indicator == "P" || PRM_mode_indicator == "R" || PRM_mode_indicator == "V")))
    {
        LOG(WARNING) << "PRM_mode_indicator eroor in " << sentence;
        std::cout << "PRM_mode_indicator is " << PRM_mode_indicator << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "PRM_mode_indicator is " << PRM_mode_indicator << "   " << sentence << std::endl;
    storage->PRM_mode_indicator = PRM_mode_indicator;
    

    std::string Pitch_demand_value;
    --error_index;
    if (!(std::getline(iss, Pitch_demand_value, ',') && size(Pitch_demand_value) != 0 && (Pitch_demand_value.find_first_not_of("0123456789.") == Pitch_demand_value.npos)))
    {
        LOG(WARNING) << "Pitch_demand_value error in " << sentence;
        //std::cout << "Pitch_demand_value is " << Pitch_demand_value << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Pitch_demand_value = stof(Pitch_demand_value); 


    std::string Pitch_mode_indicator;
    --error_index;
    if(!(std::getline(iss, Pitch_mode_indicator, ',') && (Pitch_mode_indicator == "P" || Pitch_mode_indicator == "D" || Pitch_mode_indicator == "V")))
    {
        LOG(WARNING) << "Pitch_mode_indicator eroor in " << sentence;
        std::cout << "Pitch_mode_indicator is " << Pitch_mode_indicator << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "Pitch_mode_indicator is " << Pitch_mode_indicator << "   " << sentence << std::endl;
    storage->Pitch_mode_indicator = Pitch_mode_indicator;


    std::string Operating_location_indicator;
    --error_index;
    if(!(std::getline(iss, Operating_location_indicator, ',') && (Operating_location_indicator == "B" || Operating_location_indicator == "P" || Operating_location_indicator == "S" || Operating_location_indicator == "C" || Operating_location_indicator == "E" || Operating_location_indicator == "W")))
    {
        LOG(WARNING) << "Operating_location_indicator eroor in " << sentence;
        std::cout << "Operating_location_indicator is " << Operating_location_indicator << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "Operating_location_indicator is " << Operating_location_indicator << "   " << sentence << std::endl;
    storage->Operating_location_indicator = Operating_location_indicator;


    std::string Number_of_engine_or_propeller_shaft;
    --error_index;
    if (!(std::getline(iss, Number_of_engine_or_propeller_shaft, '*') && size(Number_of_engine_or_propeller_shaft) != 0 && (Number_of_engine_or_propeller_shaft.find_first_not_of("0123456789.") == Number_of_engine_or_propeller_shaft.npos)))
    {
        LOG(WARNING) << "Number_of_engine_or_propeller_shaft error in " << sentence;
        //std::cout << "Number_of_engine_or_propeller_shaft is " << Number_of_engine_or_propeller_shaft << "   " << sentence << std::endl;
        return error_index;
    }
     storage->Number_of_engine_or_propeller_shaft = stoi(Number_of_engine_or_propeller_shaft); 

    return 1;
}

 

