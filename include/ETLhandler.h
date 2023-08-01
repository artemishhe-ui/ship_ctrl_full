#include "nmea_tools.h"

#include <iostream>
#include <iomanip>
#include <sstream>

#include "Ship_state.h"

/// @brief 
/// @param type 1 = Order, 0 = Answerback
/// @return 
std::string formETL(bool type, Ship_state * storage)
{
    std::stringstream stream;
    stream << "ETL," << getCurrentTime() << ",";
    if (type)
    {
        stream << "O,";
    }
    else
    {
        stream << "A,";
    }
    
    
    stream << std::setw(2) << std::setfill('0') << storage->get_trust_factor_state() << ","; // TODO: code 15 00 05 instead of float
    stream  << std::setw(2) << std::setfill('0') << 30 << "," ; // nav full
    stream << "B" << "," ; // brige
    stream << "0"; // single propeller shaft single engine
    return stream.str();
}

int parseETL(const std::string& sentence, Ship_state * storage)
{
    std::istringstream iss(sentence);
    std::string token;

    // skip "$U1ETL,"
    std::getline(iss, token, ',');
    
    // Extract UTC time
    if (!(std::getline(iss, token, ','))) // TODO: can be a NULL field!!!
    {
        LOG(WARNING) << "NO TIME MSG seems empty:" << sentence;
        return -2;   // no time no game
    }
    //LOG_IF(ERROR, token.contains(".")) << "NOT A TIME";
    LOG_IF(ERROR, token.find('.') == std::string::npos) << "NOT A TIME";
    LOG(INFO) << token << " hhmmss.ss";
    unsigned int hh = std::stoi(token.substr(0, 2));
    unsigned int mm = std::stoi(token.substr(2, 2));
    double       ss = std::stod(token.substr(4));
}