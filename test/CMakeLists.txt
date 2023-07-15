project(tests)

find_package (Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(test1_source test1.cpp)
set(test2_source nmea_tools_test.cpp)

add_executable(test1 ${test1_source})
add_executable(nmea_tools_test ${test2_source})



target_link_libraries(nmea_tools_test ${Boost_LIBRARIES} nmea_tools)

add_test(NAME Test1 COMMAND test1)
add_test(NAME nmea_tools_test COMMAND nmea_tools_test)


# add_test(testTkInter "/usr/bin/python" "-c" "import Tkinter")