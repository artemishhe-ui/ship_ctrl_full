///test NmeaChecksumm
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NmeaChecksum_test
#include <boost/test/included/unit_test.hpp>
//#include <boost/test/unit_test.hpp>

#include <iostream>
#include <nmea_tools.h>

BOOST_AUTO_TEST_SUITE(NmeaChecksumTests)

BOOST_AUTO_TEST_CASE(FiniteMSGTest)
{
    //Calculator calc;
    BOOST_CHECK_EQUAL( CalculateChecksum<unsigned char>("$GPRMC,222548.00,V,5959.4246,N,03019.1743,E,0.0000,0.000,310523,11.1,E*4D") , 0x4D);
}

BOOST_AUTO_TEST_CASE(EmptyMSGTest)
{
    //Calculator calc;
    BOOST_CHECK_EQUAL( CalculateChecksum<unsigned char>("$GPGSA,A,1,,,,,,,,,,,,,,,,*32") , 0x32);
}

BOOST_AUTO_TEST_CASE(FiniteMSGTeststr)
{
    std::string s = CalculateChecksum<std::string>("$GPRMC,222548.00,V,5959.4246,N,03019.1743,E,0.0000,0.000,310523,11.1,E*4D");
    char  c[] = "4D";
    //Calculator calc;
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_CASE(EmptyMSGTeststr)
{
    std::string s = CalculateChecksum<std::string>("$GPGSA,A,1,,,,,,,,,,,,,,,,*32");
    char  c[] = "32";
    //strcmp(s.c_str(),c)==0
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_CASE(FiniteMSGTest_str)
{
    //std::string st = "GAA,123,45,6,7";
    std::string s = formNMEAMessage("GAA,12,45,6,7,15");
    char  c[] = "$U0GAA,12,45,6,7,15*6C";
    //Calculator calc;
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_CASE(EmptyMSGTest_str)
{
    //std::string st = "GAA,123,,,";
    std::string s = formNMEAMessage("GAA,123,,,");
    char  c[] = "$U0GAA,123,,,*77";
    //strcmp(s.c_str(),c)==0
    BOOST_CHECK_MESSAGE( strcmp(s.c_str() , c)==0, "calc is " << s << " and should be " << c);
}

BOOST_AUTO_TEST_SUITE_END()