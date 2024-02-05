#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include "Ship_state.h"
#include <sstream>
#include <iostream>
#include "GNSSData.h"

struct ETL_container
{
    int hh;
    int mm;
    int ss;
    int ms;
    std::string Message_type;
    std::string Position_indicator_of_engine_telegraph;
    int Position_indicator_of_sub_telegraph;
    std::string Operating_location_indicator;
    int Number_of_engine_or_propeller_shaft;
};


int parseNMEA_ETL(const std::string& sentence, ETL_container* container)
{
    short error_index = -1;
    std::istringstream iss(sentence);

    std::string token;
    if (!(std::getline(iss, token, ',') && token.substr(3) == "ETL"))
    {
        LOG(FATAL) << "Token error in " << sentence;
        return error_index;
    }
    // else
    // {
    //     std::cout  << "Token is: " << token << endl;
    // }


    std::string time;
    --error_index;
    if (!(std::getline(iss, time, ',') && (size(time) == 9 || size(time) == 0)))
    {
        LOG(WARNING) << "Time error in " << sentence;
        return error_index;
    }
    // else
    // {
    //     cout << "Time is ";
    //     switch (size(time))
    //     {
    //         case 0:
    //         {
    //             cout << "NULL" << endl;
    //             break;
    //         }
    //         case 9:
    //         {
    //             cout << time.substr(0, 2) << "h " << time.substr(2, 2) << "m " << time.substr(4, 2) << "s " << time.substr(7) << "ms" << endl;
    //             break;
    //         }
    //     }
    // }
    container->hh = stoi(time.substr(0, 2));
    container->mm = stoi(time.substr(2, 2));
    container->ss = stoi(time.substr(4, 2));
    container->ms = stoi(time.substr(7, 2));

    std::string message_type;
    --error_index;
    if (!(std::getline(iss, message_type, ',') && (message_type == "O" || message_type == "A")))
    {
        LOG(WARNING)<< "Message type error in " << sentence;
        return error_index;
    }
    // else
    // {
    //     cout << "Message type is " << message_type << endl;
    // }
    container->Message_type = message_type;

    std::string position_indicator;
    --error_index;
    if (!(std::getline(iss, position_indicator, ',') && (position_indicator[0] == '0' || position_indicator[0] == '1') && std::stoi(position_indicator.substr(1)) > 0 && std::stoi(position_indicator.substr(1)) < 6))
    {
        LOG(WARNING) << "Position indicator of engine telegraph error in " << sentence;
        return error_index;
    }
    container->Position_indicator_of_engine_telegraph = position_indicator  ;
    // else
    // {
    //     cout << "Position indicator is " << position_indicator << endl;
    // }


    std::string sub_telegraph_position;
    --error_index;
    if (!(std::getline(iss, sub_telegraph_position, ',') && (std::stoi(sub_telegraph_position) == 20 || std::stoi(sub_telegraph_position) == 30 || std::stoi(sub_telegraph_position) == 40)))
    {
        LOG(WARNING) << "Position indicator of sub telegraph position error" << sentence;
        return error_index;
    }
    // else
    // {
    //     cout << "Sub telegraph position is " << sub_telegraph_position << endl;
    // }
    container->Position_indicator_of_sub_telegraph = stoi(sub_telegraph_position);


    std::string operating_location_indicator;
    --error_index;
    if (!(std::getline(iss, operating_location_indicator, ',') && (size(operating_location_indicator) == 0 || size(operating_location_indicator) == 1 && (operating_location_indicator[0] == 'B' || operating_location_indicator[0] == 'C' || operating_location_indicator[0] == 'P' || operating_location_indicator[0] == 'S' || operating_location_indicator[0] == 'E' || operating_location_indicator[0] == 'W'))))
    {
        LOG(WARNING) << "Opertaing location indicator error in " << sentence;
        return error_index;
    }
    // else
    // {
    //     cout << "operating location indicator is " << operating_location_indicator << endl;
    // }
    container->Operating_location_indicator = operating_location_indicator;


    std::string Number;
    --error_index;
    if (!(std::getline(iss, Number, '*') && (Number == "Odd" || Number == "Even" || Number == "0")))
    {
        LOG(WARNING) << "Number  of engine or propeller shaft error in " << sentence;
        return error_index;
    }
    // else
    // {
    // cout << "Number is " << Number << endl;
    // }
    container -> Number_of_engine_or_propeller_shaft = stoi(Number);


    return 1;
}

std::string generate_ETL()
{
    std::string hh = std::to_string(rand() % 24); if (size(hh) == 1) hh = "0" + hh;
    std::string mm = std::to_string(rand() % 60); if (size(mm) == 1) mm = "0" + mm;
    std::string ss = std::to_string(rand() % 60); if (size(ss) == 1) ss = "0" + ss;
    std::string ms = std::to_string(rand() % 100); if (size(ms) == 1) ms = "0" + ms;
    std::string event_time = hh + mm + ss + "." + ms;
    std::string message_type = (rand() % 2) ? "O" : "A";
    std::string position_indicator_of_engine_telegraph = std::to_string(rand() % 2) + std::to_string(rand() % 5 + 1);
    std::string position_indicator_of_sub_telegraph = std::to_string(rand() % 3 + 2) + "0";
    std::string help[7] = { "B", "P", "S", "C", "E", "W", " "};
    std::string operating_location_indicator =  help[rand() % 7];
    std::string number_of_engine_or_propeller_shaft = std::to_string(rand() % 10);
    std::string comma = ",";
    return "$--ETL" + comma + event_time + comma + message_type + comma + position_indicator_of_engine_telegraph + comma
        + position_indicator_of_sub_telegraph + comma + operating_location_indicator + comma + number_of_engine_or_propeller_shaft + comma +
        "*hh<CR><LF>";
}


std::string get_ETL(ETL_container container)
{
    std::string hh = std::to_string(container.hh); if (size(hh) == 1) hh = "0" + hh;
    std::string mm = std::to_string(container.mm); if (size(mm) == 1) mm = "0" + mm;
    std::string ss = std::to_string(container.ss); if (size(ss) == 1) ss = "0" + ss;
    std::string ms = std::to_string(container.ms); if (size(ms) == 1) ms = "0" + ms;
    std::string event_time = hh + mm + ss + "." + ms;
    std::string message_type = container.message_type;
    std::string position_indicator_of_engine_telegraph = container.position_indicator_of_engine_telegraph;
    std::string position_indicator_of_sub_telegraph = std::to_string(container.position_indicator_of_sub_telegraph);
    std::string operating_location_indicator = container.operating_location_indicator;
    std::string number_of_engine_or_propeller_shaft = std::to_string(container.number_of_engine_or_propeller_shaft);
    std::string comma = ",";
    return "$--ETL" + comma + event_time + comma + message_type + comma + position_indicator_of_engine_telegraph + comma
        + position_indicator_of_sub_telegraph + comma + operating_location_indicator + comma + number_of_engine_or_propeller_shaft + comma +
        "*hh<CR><LF>";
}
