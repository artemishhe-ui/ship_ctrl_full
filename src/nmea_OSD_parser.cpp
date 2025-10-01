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
    std::string ret_str="$--OSD,";  
    ret_str.reserve(40*sizeof(char));
    int help = rand() % 5;
    ret_str+= std::to_string(int(rand() % 100));  //heading
    ret_str+=',';
    ret_str+= (rand() % 2) ? 'A' : 'V';  //heading status
    ret_str+=',';
    ret_str+= std::to_string(int(rand() % 100));  //Vessel course
    ret_str+=',';
    ret_str+= (help == 0) ? 'M' : ((help == 1) ? 'W' : ((help == 2) ? 'R' : ((help == 3) ? 'B' : 'P')));   //Cource reference
    ret_str+=',';
    ret_str+= std::to_string(int(rand() % 100));   //Vessel speed
    ret_str+=',';
    ret_str+= (help == 0) ? 'M' : ((help == 1) ? 'W' : ((help == 2) ? 'R' : ((help == 3) ? 'B' : 'P')));    //Speed reference
    ret_str+=',';
    help = rand() % 5;
    ret_str+= std::to_string(int(rand() % 100)); //Vesset set
    ret_str+=',';
    ret_str+= std::to_string(int(rand() % 100));   //Vessel drift
    ret_str+=',';
    help = rand() % 3;
    ret_str+= (help == 0) ? 'K' : ((help == 1) ? 'N' : 'S');    //Speed Units
    ret_str+=',';
    ret_str+="*<CR><LF>";

    return ret_str;
}


std::string get_osd(const OSD_container& container)
{
    std::string ret_str="$--OSD,";  
    ret_str.reserve(40*sizeof(char));
    ret_str+= std::to_string(container.Heading); 
    ret_str+= container.Heading_status;
    ret_str+= ',';
    ret_str+= std::to_string(container.Vessel_course);
    ret_str+= ',';
    ret_str+=container.Course_reference;
    ret_str+= ',';
    ret_str+= std::to_string(container.Vessel_speed); 
    ret_str+= ',';
    ret_str+= container.Speed_reference;
    ret_str+= ',';
    ret_str+= std::to_string(container.Vesset_set);
    ret_str+= ',';
    ret_str+= std::to_string(container.Vessel_drift);
    ret_str+= ',';
    ret_str+= container.Speed_units;
    ret_str+= ',';
    ret_str+= "*<CR><LF>";

    return ret_str;
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


