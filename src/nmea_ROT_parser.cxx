#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <sstream>
#include <iostream>

struct ROT_conainer
(
    unsigned Rate_of_turn;
    std::string Status;
);


std::string generate_rot()
{
    std::string ret_str="$--ROT,";
    ret_str.reserve(30*sizeof(char));
    ret_str+=std::to_string(int(rand() % 100)); //Rate_of_turn
    ret_str+= ",";
    ret_str+=(rand() % 2) ? 'A' : 'V';  //Status
    ret_str+="*<CR><LF>"; 
    
    return ret_str;
}


std::string get_rot(const ROT_container& container)
{
    std::string ret_str="$--ROT,";
    ret_str.reserve(30*sizeof(char));
    ret_str+= std::to_string(container.Rate_of_turn);
    ret_str+= ',';
    ret_str+= container.Status;
    ret_str+= "*<CR><LF>"; 
    
    return ret_str;
}


int parseNMEA_ROT(const std::string& sentence, Ship_state * storage)
{
    short error_index = -1;
    std::istringstream iss(sentence);

    std::string token;
    if (!(std::getline(iss, token, ',') && token.substr(3) == "ROT"))
    {
        LOG(FATAL) << "Token error in " << sentence;
        return error_index;
    }

    std::string Rate_of_turn;
    --error_index;
    if (!(std::getline(iss, Rate_of_turn, ',') && size(Rate_of_turn) != 0))
    {
        LOG(WARNING) << "Rate_of_turn error in " << sentence;
        //std::cout << "Rate_of_turn is " << Rate_of_turn << "   " << sentence << std::endl;
        return error_index;
    }
    try
    {
        double test = stof(Rate_of_turn);
    }
    catch (std::invalid_argument& b)
    {
        LOG(WARNING) << "Rate_of_turn error in " << sentence;
        //std::cout << "Rate_of_turn is " << Rate_of_turn << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Rate_of_turn = stof(Rate_of_turn);

    //std::cout << "Rate_of_turn is " << Rate_of_turn << "   " << sentence << std::endl;

    std::string Status;
    --error_index;а
    if (!(std::getline(iss, Status, '*') && (Status == "A" || Status == "V")))
    {
        LOG(WARNING) << "Status eroor in " << sentence;
        //std::cout << "Status is " << Status << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "Status is " << Status << "   " << sentence << std::endl;
    storage->Status = Status;


    return 1;
}


