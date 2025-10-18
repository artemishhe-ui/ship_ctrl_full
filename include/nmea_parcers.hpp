
#define STD_NMEA_MSG_SIZE 82*sizeof(char)  //probably std isn`t the best shortcut for standart
#define EMPTY_NMEA_MSG "$aaccc, c---c*hh<CR><LF>"

#include <sstream>
#include <cstdint>
#include "ship_state.h"

enum class talkerID{
    ERR,
    GL, //GLONASS
    BD=1,   //Beidou
    GB=1,   //Beidou
    GA, //Galileo

    /*I believe there is more of these*/
};

enum class msg_type{    
    ERR=-1,
    TRC,
    RSA,
    ROT,
    ROR,
    PRM,
    PRC,
    OSD,
    HTC,
    HTD,
    ETL
};
/*//======================================================================================================
//strings that are 100% containing valid NMEA message, so validation will not be needed in every process
//======================================================================================================
class valid_string{
    private:
        std::string sentence;
        bool isValid;    //if no exception syntax
    public:
        valid_string(): sentence(""), isValid(false) {}
        valid_string(const std::string& input_str): sentence(s)
};
*/
//=================================================================================================================================================
//Parent class for all message types, basically object of this class is created to store message, do safety stuff, and create object of needed type
//=================================================================================================================================================
class Message{
    public:
    //    Message():_talkerID(talkerID::ERR), _Message(EMPTY_NMEA_MSG){}
   //    Message(const Message& other): _talkerID(other.getTalkerID()), _Message(other.getMessage()) {};
     
   
   
   /*  Message(std::stringstream input_stream){    //I probably got sth with streams wrong
            //
            Do safety things
            //
           std::ostring unparsed_msg;
           unparsed_msg<<input_stream;
           std::string ID= unparsed_msg.substr(2,2);
           switch(ID){
            case "GL": {this->_talkerID=talkerID::GL; break;}
            case "BD": {this-> _talkerID=talkerID::BD; break;}
            case "GB": {this-> _talkerID=talkerID::GB; break;}
            case "GA": {this-> _talkerID=talkerID::GA; break;}
            default: {this-> _talkerID=talkerID::ERR; break;}
           }*/
        virtual ~Message()=default;
        Message(const std::string& sentence): _talkerID(determinetalkerID(sentence)/*not written*/), _Message(sentence), _msg_type(determineMsgType(sentence) /*not written*/ {
            switch(this->_msg_type){
                case TRC: {this->valid_string_ptr = new TRC_message(sentence); break;}
                //I`ll write all cases when be no lazy
        }
        //getters
        talkerID getTalkerID() const {return this->_talkerID;}
        std::string getMessage() const {return this->_Message;}

    private:
        Message()=default;
        Message* valid_string_ptr;
        msg_type _msg_type;
    protected:
    talkerID _talkerID;
    //CHECKSUM_TYPE _expected_checksum
    std::string _Message;  
    [[nodiscard]] std::string CalculateCheckSum() const;
    [[nodiscard]] bool CheckCheckSum() const;
};


class TRC_message final : public Message_handler{
    public:
        
        TRC_message()=default;
        ~TRC_message()=default;
        TRC_message (const std::string& sentence);    //todo
        TRC_message(const Ship_state* Ship_state_info); //todo
        std::string generateTRC() const;
        std::string getTRC() const;

    private:
        static const msg_type _msg_type= msg_type::TRC;
        uint8_t Number_of_thruster;
        uint8_t PRM_demand_value;
        std::string PRM_mode_indicator;
        uint8_t Pitch_demand_value;
        std::string Pitch_mode_indicator;
        uint16_t Azimuth_demand;
        std::string Operating_location_indicator;
        std::string Sentense_status_flag;

};
