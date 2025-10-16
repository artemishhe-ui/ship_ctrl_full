

#include "nmea_parcers.hpp"
#include <iomanip>
#include <sstream>
std::string Message::CalculateCheckSum() const {

        // Exclude the starting '$' and ending '*' characters
        size_t startIndex = this->_Message.find('$') + 1;   //
        size_t endIndex = _Message.find('*');
        if (endIndex<startIndex ||startIndex==-1 || endIndex== -1){
            LOG(WARNING) << " This Message is Invalid: " << this->_Message;
            /*it probably should delete the Message object but I`ll forget about it and commit it with very funny comment*/
        }

        //I don`t get, may msgs be more than 82 symbols or not
        if (endIndex-startIndex > (STD_NMEA_MSG_SIZE/sizeof(char))){
            LOG(WARNING) << " This Message is too big: " << this->_Message;
            /*it probably should delete the Message object but I`ll forget about it and commit it with very funny comment*/
        }

    // Calculate the checksum

    //I`m pretty sure that checksum of all chars shouldn`t be initialized by zero
    unsigned char checksum=_Message[startIndex];
    for (size_t i = (startIndex+1); i < endIndex; ++i){
        checksum ^= _Message[i];
    }
    
    //I suppose that there should be better way of doing this
    std::stringstream stream;
    stream << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << checksum;
    return stream.str();
    }

bool Message::CheckCheckSum() const {
    std::string expected_checksum=CalculateCheckSum();
    size_t before_asterisk_index= this->_Message.find('*');
    if (before_asterisk_index==-1 || (this->_Message.length()-before_asterisk_index)!=3){
         LOG(WARNING) << " This Message is Invalid: " << this->_Message;
            /*it probably should delete the Message object but I`ll forget about it and commit it with very funny comment*/
    }
    std::string received_checksum= this->_Message.substr(before_asterisk_index+1, 2);

    if (expected_checksum!=received_checksum){
        LOG(WARNING) << " Wrong checksum expect(recived): " << this->_Message;
        return false;
    }
    else return true;
}    

std::string TRC_message::generateTRC() const{
    std::string ret_str="$--TRC,";
    int help = rand() % 3;
    ret_str.reserve(82 * sizeof(char));    //at most the message will be 36 chars long
    ret_str += std::to_string(int(rand() % 100));   //Number of thruster
    ret_str += ',';
    ret_str += std::to_string(int(rand() % 100));   //PRM_demand_value
    ret_str += ',';
    ret_str += (help == 0) ? 'K' : ((help == 1) ? 'N' : 'S');   //PRM_mode_indicator
    ret_str += ',';
    ret_str += std::to_string(int(rand() % 100));   //Pitch_demand_value
    ret_str += ',';
    help = rand() % 3;
    ret_str += (help == 0) ? 'V' : ((help == 1) ? 'D' : 'P');   //Pitch_mode_indicator
    ret_str += ',';
    ret_str += std::to_string(int(rand() % 360));   //Azimuth_demand
    ret_str += ',';
    help = rand() % 6;
    ret_str += (help == 0) ? 'B' : ((help == 1) ? 'P' : ((help == 2) ? 'S' : ((help == 3) ? 'C' : ((help == 4) ? 'E' : 'W'))));;    //Operating_location_indicator
    ret_str += ',';
    ret_str += (rand() % 2) ? 'C' : 'R';    //Sentense_status_flag
    ret_str += "*<CR><LF>";
    
    return ret_str;

}

std::string TRC_message::getTRC() const{
    std::string ret_str = "$--TRC,";
    ret_str.reserve(STD_NMEA_MSG_SIZE);
    ret_str += std::to_string(this->Number_of_thruster);   
    ret_str += ',';
    ret_str += std::to_string(this->PRM_demand_value); 
    ret_str += ',';
    ret_str += PRM_mode_indicator;   
    ret_str += ',';
    ret_str += std::to_string(this->Pitch_demand_value);   
    ret_str += ',';
    ret_str += PRM_mode_indicator;   
    ret_str += ',';
    ret_str += std::to_string(this->Azimuth_demand);  
    ret_str += ',';
    ret_str += Operating_location_indicator;  
    ret_str += ',';
    ret_str += Sentense_status_flag;  
    ret_str+="*<CR><LF>";
    return ret_str;
}