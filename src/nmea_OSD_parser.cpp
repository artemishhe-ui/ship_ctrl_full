#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <sstream>
#include <iostream>

struct OSD_container
(
    unsigned Heading; 
    std::string Heading_status;
    unsigned Vessel_course;
    std::string Course_reference;
    unsigned Vessel_speed;
    std::string Speed_reference;
    unsigned Vesset_set;
    unsigned Vessel_drift;
    std::string Speed_units;
);

std::string generate_osd()
{
    
    int help = rand() % 5;
    std::string Heading = std::to_string(int(rand() % 100));; 
    std::string Heading_status = (rand() % 2) ? "A" : "V";;
    std::string Vessel_course = std::to_string(int(rand() % 100));
    std::string Course_reference = (help == 0) ? "M" : ((help == 1) ? "W" : ((help == 2) ? "R" : ((help == 3) ? "B" : "P")));;
    std::string Vessel_speed = std::to_string(int(rand() % 100));
    std::string Speed_reference = (help == 0) ? "M" : ((help == 1) ? "W" : ((help == 2) ? "R" : ((help == 3) ? "B" : "P")));; ;
    help = rand() % 5;
    std::string Vesset_set = std::to_string(int(rand() % 100));
    std::string Vessel_drift = std::to_string(int(rand() % 100));
    help = rand() % 3;
    std::string Speed_units = (help == 0) ? "K" : ((help == 1) ? "N" : "S");

    return "$--OSD" + Comma + Heading + Comma + Heading_status + Comma + Vessel_course + Comma + Course_reference + Comma + 
    Vessel_speed + Comma + Speed_reference + Comma + Vesset_set + Comma + Vessel_drift + Comma + Speed_units + Comma + "*<CR><LF>";

}


std::string get_osd(OSD_container container)
{
    std::string Heading = std::to_string(container.Heading); 
    std::string Heading_status = container.Heading_status;
    std::string Vessel_course = std::to_string(container.Vessel_course);
    std::string Course_reference = container.Course_reference;
    std::string Vessel_speed = std::to_string(container.Vessel_speed); 
    std::string Speed_reference = container.Speed_reference;
    std::string Vesset_set = std::to_string(container.Vesset_set);
    std::string Vessel_drift = std::to_string(container.Vessel_drift);
    std::string Speed_units =  container.Speed_units;
    std::string Comma = ",";

    return "$--OSD" + Comma + Heading + Comma + Heading_status + Comma + Vessel_course + Comma + Course_reference + Comma + 
    Vessel_speed + Comma + Speed_reference + Comma + Vesset_set + Comma + Vessel_drift + Comma + Speed_units + Comma + "*<CR><LF>";
}



int parseNMEA_OSD(const std::string& sentence, OSD_container* storage)
{
    short error_index = -1;
    std::istringstream iss(sentence);

    std::string token;
    if (!(std::getline(iss, token, ',') && token.substr(3) == "OSD"))
    {
        LOG(FATAL) << "Token error in " << sentence;
        return error_index;
    }

    std::string Heading;
    --error_index;
    if (!(std::getline(iss, Heading, ',') && size(Heading) != 0 && (Heading.find_first_not_of("0123456789.") == Heading.npos)))
    {
        LOG(WARNING) << "Heading error in " << sentence;
        //std::cout << "Heading is " << Heading << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Heading = stof(heading);


    std::string heading_status;
    --error_index;
    if(!(std::getline(iss, heading_status, ',') && (heading_status == "A" || heading_status == "V")))
    {
        LOG(WARNING) << "heading_status eroor in " << sentence;
        std::cout << "heading_status is " << heading_status << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Heading_status = heading_status;
    //std::cout << "heading_status is " << heading_status << "   " << sentence << std::endl;

    
    std::string vessel_course;
    --error_index;
    if (!(std::getline(iss, vessel_course, ',') && size(vessel_course) != 0 && (vessel_course.find_first_not_of("0123456789.") == vessel_course.npos)))
    {
        LOG(WARNING) << "vessel_course error in " << sentence;
        //std::cout << "vessel_course is " << vessel_course << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Vessel_course = stof(vessel_course);


    std::string course_reference;
    --error_index;
    if(!(std::getline(iss, course_reference, ',') && (course_reference == "B" || course_reference == "M" || course_reference == "W" || course_reference == "R" || course_reference == "P")))
    {
        LOG(WARNING) << "course_reference eroor in " << sentence;
        std::cout << "course_reference is " << course_reference << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "course_reference is " << course_reference << "   " << sentence << std::endl;
    storage->Course_reference = course_reference;


    std::string vessel_speed;
    --error_index;
    if (!(std::getline(iss, vessel_speed, ',') && size(vessel_speed) != 0 && (Rate_of_turn.find_first_not_of("0123456789.") == vessel_speed.npos)))
    {
        LOG(WARNING) << "vessel_speed error in " << sentence;
        //std::cout << "vessel_speed is " << vessel_speed << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Vessel_speed = stof(vessel_speed);


    std::string speed_reference;
    --error_index;
    if(!(std::getline(iss, speed_reference, ',') && (speed_reference == "B" || speed_reference == "M" || speed_reference == "W" || speed_reference == "R" || speed_reference == "P")))
    {
        LOG(WARNING) << "speed_reference eroor in " << sentence;
        std::cout << "speed_reference is " << speed_reference << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Speed_reference = speed_reference;
    //std::cout << "speed_reference is " << speed_reference << "   " << sentence << std::endl;

    
    std::string vesset_set;
    --error_index;
    if (!(std::getline(iss, vesset_set, ',') && size(vesset_set) != 0 && (vesset_set.find_first_not_of("0123456789.") == vesset_set.npos)))
    {
        LOG(WARNING) << "vesset_set error in " << sentence;
        //std::cout << "vesset_set is " << vesset_set << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Vesset_set = stof(vesset_set);
  

    std::string vessel_drift;
    --error_index;
    if (!(std::getline(iss, vessel_drift, ',') && size(vessel_drift) != 0 && (vessel_drift.find_first_not_of("0123456789.") == vessel_drift.npos)))
    {
        LOG(WARNING) << "vessel_drift error in " << sentence;
        //std::cout << "vessel_drift is " << vessel_drift << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Vessel_drift = stof(vessel_drift);


    std::string speed_units;
    --error_index;
    if(!(std::getline(iss, speed_units, '*') && (speed_units == "K" || speed_units == "N" || speed_units == "S")))
    {
        LOG(WARNING) << "speed_units eroor in " << sentence;
        std::cout << "speed_units is " << speed_units << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Speed_units = stof(speed_units);


    //std::cout << "speed_units is " << speed_units << "   " << sentence << std::endl;

    return 1;
}

