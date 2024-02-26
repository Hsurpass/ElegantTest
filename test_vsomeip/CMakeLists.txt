cmake_minimum_required(VERSION 3.13)

project(helloworld)

set(CMAKE_CXX_FLAGS "-g -std=c++0x")

find_package(vsomeip3 REQUIRED)
find_package(Boost REQUIRED)

message("Boost_LIBRARIES: " ${Boost_LIBRARIES})

add_executable(helloserver server.cpp)
target_link_libraries(helloserver 
    vsomeip3
    boost_thread
    boost_system
    boost_log
)

add_executable(helloclient client.cpp)
target_link_libraries(helloclient
    vsomeip3
    boost_thread
    boost_system
    boost_log
)