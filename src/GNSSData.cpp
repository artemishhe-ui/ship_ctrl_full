#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

//#define M_PI 3.14

class GNSSData {
public:
    /// @brief defalut constructor
    GNSSData() : latitude(0.0), longitude(0.0), altitude(0.0), heading(0.0) {}

    /// @brief Data constructor
    /// @param latitude N/S latt
    /// @param longitude E/W long
    /// @param altitude alt
    /// @param heading course
    GNSSData(double latitude, double longitude, double altitude, double heading)
        : latitude(latitude), longitude(longitude), altitude(altitude), heading(heading) {}

    /// @brief pares GPGAA sentense
    ///                             ID    hhmmss.ss lat        N/S Long         W/E Qua sats Hpres  Alt     Alt unit Geosep  G unit  sec update  Ref station ID
    /// @param sentence smth like "$GPGGA,134658.00,5106.9792,  N, 11402.3003,  W,  2,  09,  1.0,   1048.47,M,       -16.27, M,      08,         AAAA * 60"
    /// @return sucsess/fail
    bool parseNMEASentence(const std::string& sentence) {
        std::istringstream iss(sentence);
        std::string token;

        // Check if the sentence is a GGA sentence
        if (!(std::getline(iss, token, ',') && token == "$GPGGA")) {
            LOG(ERROR) << "Wrong message";
            
            return false;
        }
        // Extract UTC time
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        //LOG_IF(ERROR, token.contains(".")) << "NOT A TIME";
        LOG_IF(ERROR, token.find('.') == std::string::npos) << "NOT A TIME";
        LOG(INFO) << token << " hhmmss.ss";
        unsigned int hh = std::stoi(token.substr(0, 2));
        unsigned int mm = std::stoi(token.substr(2, 2));
        double       ss = std::stod(token.substr(4));
        // Extract latitude
        if (!(std::getline(iss, token, ','))) {
            return false;
        }

        double latDegrees = std::stod(token.substr(0, 2));
        double latMinutes = std::stod(token.substr(2));
        latitude = latDegrees + latMinutes / 60.0;

        // Extract latitude hemisphere (N/S)
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        if (token == "S") {
            latitude *= -1.0;
        }

        // Extract longitude
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        double lonDegrees = std::stod(token.substr(0, 3));
        double lonMinutes = std::stod(token.substr(3));
        longitude = lonDegrees + lonMinutes / 60.0;

        // Extract longitude hemisphere (E/W)
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        if (token == "W") {
            longitude *= -1.0;
        }

        // Extract Quality ID
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        int Q_ID = std::stoi(token);

        // Extract Number of satellites in use. May be different to the number in view
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        int sats = std::stoi(token);

        // Extract Horizontal dilution of precision
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        double Hpres = std::stod(token);

        // Extract altitude
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        altitude = std::stod(token);

        // Extract altitude Units
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        LOG_IF(INFO, token.compare("M") != 0) << "NOT IN CI UNITS!!!";

        // Extract Undulation - the relationship between the geoid and the WGS84 ellipsoid
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        double undulation = std::stod(token);

        // Extract Units of undulation (M = metres)
        if (!(std::getline(iss, token, ','))) {
            return false;
        }
        LOG_IF(INFO, token.compare("M") != 0) << "NOT IN CI UNITS!!!";

        // Extract Age of correction data(in seconds)
        // The maximum age reported here is limited to 99 seconds.
        if (!(std::getline(iss, token, ','))) {
            return false;
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
        return true;
    }

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }

    double getAltitude() const {
        return altitude;
    }

    double getHeading() const {
        return heading;
    }

    void setLatitude(double latitude) {
        this->latitude = latitude;
    }

    void setLongitude(double longitude) {
        this->longitude = longitude;
    }

    void setAltitude(double altitude) {
        this->altitude = altitude;
    }

    void setHeading(double heading) {
        this->heading = heading;
    }

    double calculateDistanceTo(const GNSSData& other) const {
        double earthRadius = 6371e3; // Earth radius in meters

        double lat1 = degreesToRadians(latitude);
        double lon1 = degreesToRadians(longitude);
        double lat2 = degreesToRadians(other.latitude);
        double lon2 = degreesToRadians(other.longitude);

        double deltaLat = lat2 - lat1;
        double deltaLon = lon2 - lon1;

        double a = std::sin(deltaLat / 2) * std::sin(deltaLat / 2) +
            std::cos(lat1) * std::cos(lat2) *
            std::sin(deltaLon / 2) * std::sin(deltaLon / 2);

        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

        double distance = earthRadius * c;
        return distance;
    }

private:
    double latitude;
    double longitude;
    double altitude;
    double heading;

    double degreesToRadians(double degrees) const {
        return degrees * M_PI / 180.0;
    }
};
