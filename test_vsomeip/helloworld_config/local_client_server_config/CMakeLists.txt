# cmake -B build -DCMAKE_PREFIX_PATH=xxx/vsomeip/install
cmake_minimum_required(VERSION 3.13)

project(helloworld)

set(CMAKE_CXX_FLAGS "-g -std=c++0x")

find_package(Boost REQUIRED)
message("BOOST_FOUND: " ${BOOST_FOUND})
message("BOOST_INCLUDE_DIR: " ${BOOST_INCLUDE_DIRS})
message("Boost_LIBRARIES: " ${BOOST_LIBRARIES})

find_package(vsomeip3 REQUIRED)
message("VSOMEIP3_FOUND: " ${VSOMEIP_FOUND})
message("VSOMEIP3_INCLUDE_DIR: " ${VSOMEIP_INCLUDE_DIR})
message("VSOMEIP3_LIBRARIES: " ${VSOMEIP3_LIBRARIES})


add_executable(helloserver server.cpp)
target_link_libraries(helloserver 
    vsomeip3
    pthread
    boost_thread
    boost_system
    boost_log
)

add_executable(helloclient client.cpp)
target_link_libraries(helloclient
    vsomeip3
    pthread
    boost_thread
    boost_system
    boost_log
)