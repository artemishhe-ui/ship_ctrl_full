#pragma once

#define GOOGLE_STRIP_LOG 1    // this must go before the #include!
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <sstream>
#include <iostream>
#include "GNSSData.h"


int parseNMEA_HTC(const std::string& sentence, GNSSData *storage)
{
    short error_index = -1;
std::istringstream iss(sentence);


    std::string token;
    --error_index;
    if (!(std::getline(iss, token, ',') && token.substr(3) == "HTC"))
    {
       LOG(FATAL)<< "Message type error in " << sentence;
       return error_index;
    }


    std::string override;
    --error_index;
    if(!(std::getline(iss, override, ',') && (override == "A" || override == "V")))
    {
        LOG(WARNING) << "override eroor in " << sentence;
        //std::cout << "override is " << override << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "override is " << override << "   " << sentence << std::endl;
    storage->Override = override;

    std::string commanded_rudder_angle;
    --error_index;
    if (!(std::getline(iss, commanded_rudder_angle, ',') && size(commanded_rudder_angle) != 0 && (commanded_rudder_angle.find_first_not_of("0123456789.") == commanded_rudder_angle.npos)))
    {
        LOG(WARNING) << "commanded_rudder_angle error in " << sentence;
        //std::cout << "commanded_rudder_angle is " << commanded_rudder_angle << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_rudder_angle = stof(commanded_rudder_angle);


    std::string commanded_rudder_direction;
    --error_index;
    if(!(std::getline(iss, commanded_rudder_direction, ',') && (commanded_rudder_direction == "L" || commanded_rudder_direction == "R")))
    {
        LOG(WARNING) << "commanded_rudder_direction eroor in " << sentence;
        //std::cout << "commanded_rudder_direction is " << commanded_rudder_direction << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Commanded_rudder_direction = commanded_rudder_direction;
    //std::cout << "commanded_rudder_direction is " << commanded_rudder_direction << "   " << sentence << std::endl;


    std::string selected_steering_mode;
    --error_index;
    if(!(std::getline(iss, selected_steering_mode, ',') && (selected_steering_mode == "M" || selected_steering_mode == "S" || selected_steering_mode == "H" || selected_steering_mode == "R" || selected_steering_mode == "T")))
    {
        LOG(WARNING) << "selected_steering_mode eroor in " << sentence;
        //std::cout << "selected_steering_mode is " << selected_steering_mode << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Selected_steering_mode = selected_steering_mode;
    //std::cout << "selected_steering_mode is " << selected_steering_mode << "   " << sentence << std::endl;

    
    std::string turn_mode;
    --error_index;
    if(!(std::getline(iss, turn_mode, ',') && (turn_mode == "R" || turn_mode == "T" || turn_mode == "N")))
    {
        LOG(WARNING) << "turn_mode eroor in " << sentence;
        //std::cout << "turn_mode is " << turn_mode << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "turn_mode is " << turn_mode << "   " << sentence << std::endl;
    storage->Turn_mode = turn_mode;


    std::string commanded_rudder_limit;
    --error_index;
    if (!(std::getline(iss, commanded_rudder_limit, ',') && size(commanded_rudder_limit) != 0 && (commanded_rudder_limit.find_first_not_of("0123456789.") == commanded_rudder_limit.npos)))
    {
        LOG(WARNING) << "commanded_rudder_limit error in " << sentence;
        //std::cout << "commanded_rudder_limit is " << commanded_rudder_limit << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_rudder_limit = stof(commanded_rudder_limit);


    std::string commanded_off_heading_limit;
    --error_index;
    if (!(std::getline(iss, commanded_off_heading_limit, ',') && size(commanded_off_heading_limit) != 0 && (commanded_off_heading_limit.find_first_not_of("0123456789.") == commanded_off_heading_limit.npos)))
    {
        LOG(WARNING) << "commanded_off_heading_limit error in " << sentence;
        //std::cout << "commanded_off_heading_limit is " << commanded_off_heading_limit << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_off_heading_limit = stof(commanded_off_heading_limit);


    std::string commanded_radius_of_turn;
    --error_index;
    if (!(std::getline(iss, сommanded_radius_of_turn, ',') && size(сommanded_radius_of_turn) != 0 && (сommanded_radius_of_turn.find_first_not_of("0123456789.") == сommanded_radius_of_turn.npos)))
    {
        LOG(WARNING) << "сommanded_radius_of_turn error in " << sentence;
        //std::cout << "сommanded_radius_of_turn is " << сommanded_radius_of_turn << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_radius_of_turn = stof(commanded_radius_of_turn);


    std::string commanded_rate_of_turn;
    --error_index;
    if (!(std::getline(iss, commanded_rate_of_turn, ',') && size(commanded_rate_of_turn) != 0 && (commanded_rate_of_turn.find_first_not_of("0123456789.") == commanded_rate_of_turn.npos)))
    {
        LOG(WARNING) << "commanded_rate_of_turn error in " << sentence;
        //std::cout << "commanded_rate_of_turn is " << commanded_rate_of_turn << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_rate_of_turn = stof(commanded_rate_of_turn);


    std::string commanded_heading_to_steer;
    --error_index;
    if (!(std::getline(iss, commanded_heading_to_steer, ',') && size(commanded_heading_to_steer) != 0 && (commanded_heading_to_steer.find_first_not_of("0123456789.") == commanded_heading_to_steer.npos)))
    {
        LOG(WARNING) << "commanded_heading_to_steer error in " << sentence;
        //std::cout << "commanded_heading_to_steer is " << commanded_heading_to_steer << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_heading_to_steer = stof(commanded_heading_to_steer);

    std::string сommanded_off_track_limit;
    --error_index;
    if (!(std::getline(iss, сommanded_off_track_limit, ',') && size(сommanded_off_track_limit) != 0 && (сommanded_off_track_limit.find_first_not_of("0123456789.") == сommanded_off_track_limit.npos)))
    {
        LOG(WARNING) << "сommanded_off_track_limit error in " << sentence;
        //std::cout << "сommanded_off_track_limit is " << сommanded_off_track_limit << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_off_track_limit = stof(сommanded_off_track_limit);


    std::string commanded_track;
    --error_index;
    if (!(std::getline(iss, commanded_track, ',') && size(commanded_track) != 0 && (commanded_track.find_first_not_of("0123456789.") == commanded_track.npos)))
    {
        LOG(WARNING) << "commanded_track error in " << sentence;
        //std::cout << "commanded_track is " << commanded_track << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_track = stof(commanded_track);


    std::string heading_reference_in_use;
    --error_index;
    if(!(std::getline(iss, heading_reference_in_use, ',') && (heading_reference_in_use == "T" || heading_reference_in_use == "M")))
    {
        LOG(WARNING) << "heading_reference_in_use eroor in " << sentence;
        //std::cout << "heading_reference_in_use is " << heading_reference_in_use << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Heading_reference_in_use = heading_reference_in_use;
    //std::cout << "heading_reference_in_use is " << heading_reference_in_use << "   " << sentence << std::endl;

    std::string sentence_status;
    --error_index;
    if(!(std::getline(iss, sentence_status, '*') && (sentence_status == "T" || sentence_status == "M")))
    {
        LOG(WARNING) << "sentence_status eroor in " << sentence;
        //std::cout << "sentence_status is " << sentence_status << "   " << sentence << std::endl;
        return error_index;
    }

    return 1;
}


int parseNMEA_HTD(const std::string& sentence, GNSSData *storage)
{
    short error_index = -1;
    std::istringstream iss(sentence);

    std::string token;
    --error_index;
    if (!(std::getline(iss, token, ',') && token.substr(3) == "HTD"))
    {
       LOG(FATAL)<< "Message type error in " << sentence;
       return error_index;
    }

    std::string override;
    --error_index;
    if(!(std::getline(iss, override, ',') && (override == "A" || override == "V")))
    {
        LOG(WARNING) << "override eroor in " << sentence;
        //std::cout << "override is " << override << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "override is " << override << "   " << sentence << std::endl;
    storage->Override = override;

    std::string commanded_rudder_angle;
    --error_index;
    if (!(std::getline(iss, commanded_rudder_angle, ',') && size(commanded_rudder_angle) != 0 && (commanded_rudder_angle.find_first_not_of("0123456789.") == commanded_rudder_angle.npos)))
    {
        LOG(WARNING) << "commanded_rudder_angle error in " << sentence;
        //std::cout << "commanded_rudder_angle is " << commanded_rudder_angle << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_rudder_angle = stof(commanded_rudder_angle);


    std::string commanded_rudder_direction;
    --error_index;
    if(!(std::getline(iss, commanded_rudder_direction, ',') && (commanded_rudder_direction == "L" || commanded_rudder_direction == "R")))
    {
        LOG(WARNING) << "commanded_rudder_direction eroor in " << sentence;
        //std::cout << "commanded_rudder_direction is " << commanded_rudder_direction << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Commanded_rudder_direction = commanded_rudder_direction;
    //std::cout << "commanded_rudder_direction is " << commanded_rudder_direction << "   " << sentence << std::endl;


    std::string selected_steering_mode;
    --error_index;
    if(!(std::getline(iss, selected_steering_mode, ',') && (selected_steering_mode == "M" || selected_steering_mode == "S" || selected_steering_mode == "H" || selected_steering_mode == "R" || selected_steering_mode == "T")))
    {
        LOG(WARNING) << "selected_steering_mode eroor in " << sentence;
        //std::cout << "selected_steering_mode is " << selected_steering_mode << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Selected_steering_mode = selected_steering_mode;
    //std::cout << "selected_steering_mode is " << selected_steering_mode << "   " << sentence << std::endl;

    
    std::string turn_mode;
    --error_index;
    if(!(std::getline(iss, turn_mode, ',') && (turn_mode == "R" || turn_mode == "T" || turn_mode == "N")))
    {
        LOG(WARNING) << "turn_mode eroor in " << sentence;
        //std::cout << "turn_mode is " << turn_mode << "   " << sentence << std::endl;
        return error_index;
    }
    //std::cout << "turn_mode is " << turn_mode << "   " << sentence << std::endl;
    storage->Turn_mode = turn_mode;


    std::string commanded_rudder_limit;
    --error_index;
    if (!(std::getline(iss, commanded_rudder_limit, ',') && size(commanded_rudder_limit) != 0 && (commanded_rudder_limit.find_first_not_of("0123456789.") == commanded_rudder_limit.npos)))
    {
        LOG(WARNING) << "commanded_rudder_limit error in " << sentence;
        //std::cout << "commanded_rudder_limit is " << commanded_rudder_limit << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_rudder_limit = stof(commanded_rudder_limit);


    std::string commanded_off_heading_limit;
    --error_index;
    if (!(std::getline(iss, commanded_off_heading_limit, ',') && size(commanded_off_heading_limit) != 0 && (commanded_off_heading_limit.find_first_not_of("0123456789.") == commanded_off_heading_limit.npos)))
    {
        LOG(WARNING) << "commanded_off_heading_limit error in " << sentence;
        //std::cout << "commanded_off_heading_limit is " << commanded_off_heading_limit << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_off_heading_limit = stof(commanded_off_heading_limit);


    std::string commanded_radius_of_turn;
    --error_index;
    if (!(std::getline(iss, сommanded_radius_of_turn, ',') && size(сommanded_radius_of_turn) != 0 && (сommanded_radius_of_turn.find_first_not_of("0123456789.") == сommanded_radius_of_turn.npos)))
    {
        LOG(WARNING) << "сommanded_radius_of_turn error in " << sentence;
        //std::cout << "сommanded_radius_of_turn is " << сommanded_radius_of_turn << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_radius_of_turn = stof(commanded_radius_of_turn);


    std::string commanded_rate_of_turn;
    --error_index;
    if (!(std::getline(iss, commanded_rate_of_turn, ',') && size(commanded_rate_of_turn) != 0 && (commanded_rate_of_turn.find_first_not_of("0123456789.") == commanded_rate_of_turn.npos)))
    {
        LOG(WARNING) << "commanded_rate_of_turn error in " << sentence;
        //std::cout << "commanded_rate_of_turn is " << commanded_rate_of_turn << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_rate_of_turn = stof(commanded_rate_of_turn);


    std::string commanded_heading_to_steer;
    --error_index;
    if (!(std::getline(iss, commanded_heading_to_steer, ',') && size(commanded_heading_to_steer) != 0 && (commanded_heading_to_steer.find_first_not_of("0123456789.") == commanded_heading_to_steer.npos)))
    {
        LOG(WARNING) << "commanded_heading_to_steer error in " << sentence;
        //std::cout << "commanded_heading_to_steer is " << commanded_heading_to_steer << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_heading_to_steer = stof(commanded_heading_to_steer);

    std::string сommanded_off_track_limit;
    --error_index;
    if (!(std::getline(iss, сommanded_off_track_limit, ',') && size(сommanded_off_track_limit) != 0 && (сommanded_off_track_limit.find_first_not_of("0123456789.") == сommanded_off_track_limit.npos)))
    {
        LOG(WARNING) << "сommanded_off_track_limit error in " << sentence;
        //std::cout << "сommanded_off_track_limit is " << сommanded_off_track_limit << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_off_track_limit = stof(сommanded_off_track_limit);


    std::string commanded_track;
    --error_index;
    if (!(std::getline(iss, commanded_track, ',') && size(commanded_track) != 0 && (commanded_track.find_first_not_of("0123456789.") == commanded_track.npos)))
    {
        LOG(WARNING) << "commanded_track error in " << sentence;
        //std::cout << "commanded_track is " << commanded_track << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Commanded_track = stof(commanded_track);


    std::string heading_reference_in_use;
    --error_index;
    if(!(std::getline(iss, heading_reference_in_use, ',') && (heading_reference_in_use == "T" || heading_reference_in_use == "M")))
    {
        LOG(WARNING) << "heading_reference_in_use eroor in " << sentence;
        //std::cout << "heading_reference_in_use is " << heading_reference_in_use << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Heading_reference_in_use = heading_reference_in_use;
    //std::cout << "heading_reference_in_use is " << heading_reference_in_use << "   " << sentence << std::endl;

    
    std::string rudder_status;
    --error_index;
    if(!(std::getline(iss, rudder_status, ',') && (rudder_status == "A" || rudder_status == "V")))
    {
        LOG(WARNING) << "rudder_status eroor in " << sentence;
        //std::cout << "rudder_status is " << rudder_status << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Rudder_status = rudder_status;
    //std::cout << "rudder_status is " << rudder_status << "   " << sentence << std::endl;

    
    std::string off_heading_status;
    --error_index;
    if(!(std::getline(iss, off_heading_status, ',') && (off_heading_status == "A" || off_heading_status == "V")))
    {
        LOG(WARNING) << "off_heading_status eroor in " << sentence;
        //std::cout << "off_heading_status is " << off_heading_status << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Off_heading_status = off_heading_status;
    //std::cout << "off_heading_status is " << off_heading_status << "   " << sentence << std::endl;


    std::string off_track_status;
    --error_index;
    if(!(std::getline(iss, off_track_status, ',') && (off_track_status == "A" || off_track_status == "V")))
    {
        LOG(WARNING) << "off_track_status eroor in " << sentence;
        //std::cout << "off_track_status is " << off_track_status << "   " << sentence << std::endl;
        return error_index;
    }
    storage->Off_track_status = off_track_status;
    //std::cout << "off_track_status is " << off_track_status << "   " << sentence << std::endl;


    std::string vessel_heading;
    --error_index;
    if (!(std::getline(iss, vessel_heading, '*') && size(vessel_heading) != 0 && (Rate_of_turn.find_first_not_of("0123456789.") == vessel_heading.npos)))
    {
        LOG(WARNING) << "vessel_heading error in " << sentence;
        //std::cout << "vessel_heading is " << vessel_heading << "   " << sentence << std::endl;
        return error_index;
    } 
    storage->Vessel_heading = vessel_heading;

    return 1;
}
