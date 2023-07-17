#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "GNSSData.h"

    /// @brief pares GPGAA sentense
    ///                             ID    hhmmss.ss lat        N/S Long         W/E Qua sats Hpres  Alt     Alt unit Geosep  G unit  sec update  Ref station ID
    /// @param sentence smth like "$GPGGA,134658.00,5106.9792,  N, 11402.3003,  W,  2,  09,  1.0,   1048.47,M,       -16.27, M,      08,         AAAA * 60"
    /// @param storage GNSSData obj ref to fill GNSSData() : latitude(0.0), longitude(0.0), altitude(0.0), heading(0.0) {}
    /// @return sucsess/fail
    int parseNMEA_GAA(const std::string& sentence, GNSSData * storage) {
        std::istringstream iss(sentence);
        std::string token;

        // reCheck if the sentence is a GGA sentence
        std::getline(iss, token, ',');
        /*
        if (!(std::getline(iss, token, ',') && token.substr(2) == "GGA")) { // TODO: split & prod err warn
            LOG(FATAL) << "Wrong message expect GGA got: " << sentence;
            
            return -1;
        }*/
        // Extract UTC time
        if (!(std::getline(iss, token, ','))) {
            LOG(WARNING) << "NO TIME MSG seems empty:" << sentence;
            return -2;   // no time no game
        }
        //LOG_IF(ERROR, token.contains(".")) << "NOT A TIME";
        LOG_IF(ERROR, token.find('.') == std::string::npos) << "NOT A TIME";
        LOG(INFO) << token << " hhmmss.ss";
        unsigned int hh = std::stoi(token.substr(0, 2));
        unsigned int mm = std::stoi(token.substr(2, 2));
        double       ss = std::stod(token.substr(4));
        
        // Extract latitude
        if (!(std::getline(iss, token, ','))) {
            return -3; // no lat means no lon also no reason to continue
        }

        double latDegrees = std::stod(token.substr(0, 2));
        double latMinutes = std::stod(token.substr(2));
        storage->setLatitude(latDegrees + latMinutes / 60.0);

        // Extract latitude hemisphere (N/S)
        if (!(std::getline(iss, token, ','))) {
            return -4;
        }
        if (token == "S") {
            storage->setLatitude(-1.0*(latDegrees + latMinutes / 60.0));
        }

        // Extract longitude
        if (!(std::getline(iss, token, ','))) {
            LOG(WARNING) << "Got lat:" << storage->getLatitude() << " But no lon! MSG: " << sentence;
            return -5;
        }
        double lonDegrees = std::stod(token.substr(0, 3));
        double lonMinutes = std::stod(token.substr(3));
        storage->setLongitude(lonDegrees + lonMinutes / 60.0);

        // Extract longitude hemisphere (E/W)
        if (!(std::getline(iss, token, ','))) {
            return -6;
        }
        if (token == "W") {
            storage->setLongitude(-1.0*(lonDegrees + lonMinutes / 60.0));
        }

        // Extract Quality ID
        if (!(std::getline(iss, token, ','))) {
            //return false;
            LOG(WARNING) << "NO Quality ID";
        }
        else
        {
            int Q_ID = std::stoi(token);
        }        

        // Extract Number of satellites in use. May be different to the number in view
        if (!(std::getline(iss, token, ','))) {
            //return false;
            LOG(WARNING) << "EMPTY Sats in view";
        }
        else
        {
            int sats = std::stoi(token);
        }
        
        // Extract Horizontal dilution of precision
        if (!(std::getline(iss, token, ','))) {
            //return false;
            LOG(WARNING) << "EMPTY Horizontal dilution of precision";
        }
        else
        {
            double Hpres = std::stod(token);
        }

        // Extract altitude
        if (!(std::getline(iss, token, ','))) {
            LOG(INFO) << "NO 3D fix alt is empty";
            return -7; // no need to continue
        }
        else
        {
            storage->setAltitude( std::stod(token) );
        }
        
        // Extract altitude Units
        if (!(std::getline(iss, token, ','))) {
            LOG(ERROR) << "Got alt but no alt units in: " << sentence;
            return -8;
        }
        LOG_IF(INFO, token.compare("M") != 0) << "NOT IN CI UNITS!!!";

        #ifdef SKIP_TAIL
        return 0;
        #endif

        // Extract Undulation - the relationship between the geoid and the WGS84 ellipsoid
        if (!(std::getline(iss, token, ','))) {
            return -9;
        }
        double undulation = std::stod(token); // TODO: do we need this? parse whatever?

        // Extract Units of undulation (M = metres)
        if (!(std::getline(iss, token, ','))) {
            return -10;
        }
        LOG_IF(INFO, token.compare("M") != 0) << "NOT IN CI UNITS!!!";

        // Extract Age of correction data(in seconds)
        // The maximum age reported here is limited to 99 seconds.
        if (!(std::getline(iss, token, ','))) {
            return -11;
        }
        double age = std::stod(token);
        LOG(INFO) << "Age of data is: " << age << " ss";
        LOG_IF(ERROR, token.empty()) << "NO DIFF DATA PRESENT";

        /* Extract heading 
        * TODO: THERE IS NO HEADING IN GPGAA
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        heading = std::stod(token);
        */
        return 0;
    }