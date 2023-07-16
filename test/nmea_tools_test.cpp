///test NmeaChecksumm
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NmeaChecksum_test
#include <boost/test/included/unit_test.hpp>
//#include <boost/test/unit_test.hpp>

#include <iostream>
#include <nmea_tools.h>

BOOST_AUTO_TEST_SUITE(NmeaChecksumTests)

BOOST_AUTO_TEST_CASE(FiniteMSG_checksumm_Test)
{
    //Calculator calc;
    BOOST_CHECK_EQUAL( CalculateChecksum<unsigned char>("$GPRMC,222548.00,V,5959.4246,N,03019.1743,E,0.0000,0.000,310523,11.1,E*4D") , 0x4D);
}

BOOST_AUTO_TEST_CASE(EmptyMSG_checksumm_Test)
{
    //Calculator calc;
    BOOST_CHECK_EQUAL( CalculateChecksum<unsigned char>("$GPVTG,089.0,T,,,15.2,N,,,*53") , 0x53);
}

BOOST_AUTO_TEST_CASE(FiniteMSG_checksumm_Teststr)
{
    std::string s = CalculateChecksum<std::string>("$GPRMC,222548.00,V,5959.4246,N,03019.1743,E,0.0000,0.000,310523,11.1,E*4D");
    char  c[] = "4D";
    //Calculator calc;
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_CASE(EmptyMSG_checksumm_Teststr)
{
    std::string s = CalculateChecksum<std::string>("$GPGSA,A,1,,,,,,,,,,,,,,,,*32");
    char  c[] = "32";
    //strcmp(s.c_str(),c)==0
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_CASE(FiniteMSG_form_Test_str)
{
    //std::string st = "GAA,123,45,6,7";
    std::string s = formNMEAMessage("GAA,12,45,6,7,15");
    char  c[] = "$U0GAA,12,45,6,7,15*6C";
    //Calculator calc;
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_CASE(EmptyMSG_form_Test_str)
{
    //std::string st = "GAA,123,,,";
    std::string s = formNMEAMessage("GAA,123,,,");
    char  c[] = "$U0GAA,123,,,*77";
    //strcmp(s.c_str(),c)==0
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_CASE(FiniteMSG_form_talker_Test_str)
{
    //std::string st = "GAA,123,45,6,7";
    std::string s = formNMEAMessage("GAA,12,45.66,6,7,15","U1");
    char  c[] = "$U1GAA,12,45.66,6,7,15*42";
    //Calculator calc;
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_CASE(EmptyMSG_form_talker_Test_str)
{
    //std::string st = "GAA,123,,,";
    std::string s = formNMEAMessage("GAA,12,,,","U1");
    char  c[] = "$U1GAA,12,,,*44";
    //strcmp(s.c_str(),c)==0
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_SUITE_END()