#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#include <iostream>
#include <chrono>
#include <time.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>


/// @brief Function to calculate the NMEA 0183 checksum
/// @param sentence NMEA 0183 MSG $GPGAA,,,,,*CS
/// @return NMEA 0183 checksum as unsigned char or string
template<typename T> T  CalculateChecksum(const std::string& sentence);


/// @brief validate the NMEA 0183 checksum
/// @param sentence NMEA 0183 MSG $GPGAA,,,,,*CS
/// @return true on OK
bool CheckChecksum(const std::string& sentence);

/// @brief form MSG
/// @param sentence all exept talker ID and Checksumm 
/// @return complete MSG
std::string formNMEAMessage(const std::string& sentence, const std::string talk_id = "U0");

/// @brief systemtime in NMEA format
/// @return hhmmss.ss
std::string getCurrentTime();


/// @brief float to int5
/// @param value -1 to +1 float
/// @return -5 to +5 int
int convertFloatToInteger5(float value);