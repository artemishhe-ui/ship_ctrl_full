project(Nmea_communication)

set( nmea_com_source nmea_com.cpp )
add_library( nmea_com_shared SHARED ${nmea_com_source} )

#set( nmea_com_source nmea_com.cpp )
add_library( nmea_com_static STATIC ${nmea_com_source} )

set( nmea_tools_source nmea_tools.cpp )
add_library( nmea_tools STATIC ${nmea_tools_source} )

target_link_libraries(nmea_tools
  glog::glog
)
