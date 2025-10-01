#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <sstream>
#include <iostream>


struct TRC_container
{
    unsigned Number_of_thruster;
    unsigned PRM_demand_value;
    std::string PRM_mode_indicator;
    unsigned Pitch_demand_value;
    std::string Pitch_mode_indicator;
    unsigned Azimuth_demand;
    std::string Operating_location_indicator;
    std::string Sentense_status_flag;
};

std::string generate_trc() {
    std::string ret_str="$--TRC,";
    int help = rand() % 3;
    ret_str.reserve(40 * sizeof(char));    //at most the message will be 40 chars long
    ret_str += std::to_string(int(rand() % 100));   //Number of thruster
    ret_str += ',';
    ret_str += std::to_string(int(rand() % 100));   //PRM_demand_value
    ret_str += ',';
    ret_str += (help == 0) ? 'K' : ((help == 1) ? 'N' : 'S');   //PRM_mode_indicator
    ret_str += ',';
    ret_str += std::to_string(int(rand() % 100));   //Pitch_demand_value
    ret_str += ',';
    help = rand() % 3;
    ret_str += (help == 0) ? 'V' : ((help == 1) ? 'D' : 'P');   //Pitch_mode_indicator
    ret_str += ',';
    ret_str += std::to_string(int(rand() % 360));   //Azimuth_demand
    ret_str += ',';
    help = rand() % 6;
    ret_str += (help == 0) ? 'B' : ((help == 1) ? 'P' : ((help == 2) ? 'S' : ((help == 3) ? 'C' : ((help == 4) ? 'E' : 'W'))));;    //Operating_location_indicator
    ret_str += ',';
    ret_str += (rand() % 2) ? 'C' : 'R';    //Sentense_status_flag
    ret_str += "*<CR><LF>";
    
    return ret_str;
}


std::string get_trc(const TRC_container& container)
{
    std::string ret_str = "$--TRC,";
    ret_str.reserve(40 * sizeof(char));
    ret_str += std::to_string(container.Number_of_thruster);   
    ret_str += ',';
    ret_str += std::to_string(container.PRM_demand_value); 
    ret_str += ',';
    ret_str += container.PRM_mode_indicator;   
    ret_str += ',';
    ret_str += std::to_string(container.Pitch_demand_value);   
    ret_str += ',';
    ret_str += container.PRM_mode_indicator;   
    ret_str += ',';
    ret_str += std::to_string(container.Azimuth_demand);  
    ret_str += ',';
    ret_str += container.Operating_location_indicator;  
    ret_str += ',';
    ret_str += container.Sentense_status_flag;  
    ret_str+="*<CR><LF>";
    return ret_str;
}



int parseNMEA_TRC(const std::string& sentence, TRC_container * storage)
{
    short error_index = -1;
    std::istringstream iss(sentence);

    std::string token;
    if (!(std::getline(iss, token, ',') && token.substr(3) == "TRC"))
    {
        LOG(FATAL) << "Token error in " << sentence;
        return error_index;
    }

    std::string Number_of_thruster;
    --error_index;
    if (!(std::getline(iss, Number_of_thruster, ',') && size(Number_of_thruster) != 0 && (Number_of_thruster.find_first_not_of("0123456789.") == Number_of_thruster.npos)))
    {
        LOG(WARNING) << "Number_of_thruster error in " << sentence;
        //std::cout << "Number_of_thruster is " << Number_of_thruster << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Number_of_thruster = stof(Number_of_thruster);
    


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
    


    std::string Azimuth_demand;
    --error_index;
    if (!(std::getline(iss, Azimuth_demand, ',') && size(Azimuth_demand) != 0 && (Azimuth_demand.find_first_not_of("0123456789.") == Azimuth_demand.npos)))
    {
        LOG(WARNING) << "Azimuth_demand error in " << sentence;
        //std::cout << "Azimuth_demand is " << Azimuth_demand << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Azimuth_demand = stof(Azimuth_demand);
    


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
    


    std::string Sentense_status_flag;
    --error_index;
    if(!(std::getline(iss, Sentense_status_flag, '*') && (Sentense_status_flag == "R" || Sentense_status_flag == "C")))
    {
        LOG(WARNING) << "Sentense_status_flag eroor in " << sentence;
        std::cout << "Sentense_status_flag is " << Sentense_status_flag << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "Sentense_status_flag is " << Sentense_status_flag << "   " << sentence << std::endl;
    storage->Sentense_status_flag = Sentense_status_flag;


    return 1;
}    

