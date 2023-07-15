///test sample
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE First_TestSuite
#include <boost/test/included/unit_test.hpp>
//#include <boost/test/unit_test.hpp>

#include <iostream>
//#include <calc.h>

BOOST_AUTO_TEST_SUITE(CalculatorTests)

BOOST_AUTO_TEST_CASE(PlusTest)
{
    //Calculator calc;
    BOOST_CHECK_EQUAL( 1 + 2 , 3);
}

BOOST_AUTO_TEST_CASE(MinusTest)
{
    //Calculator calc;
    BOOST_CHECK_EQUAL( 2 - 1 , 1);
}

BOOST_AUTO_TEST_SUITE_END()