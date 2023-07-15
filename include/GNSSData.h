#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

//#define M_PI 3.14

/// @brief GNSSData class store and simple calc
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

    inline double degreesToRadians(double degrees) const {
        return degrees * M_PI / 180.0;
    }
};
