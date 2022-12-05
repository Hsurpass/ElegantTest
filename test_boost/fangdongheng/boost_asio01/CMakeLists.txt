cmake_minimum_required (VERSION 2.8)

project(BOOST_ASIO01)

FIND_PACKAGE(Boost REQUIRED COMPONENTS system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

message(STATUS "Boost_FOUND:" ${Boost_FOUND})
MESSAGE("CMAKE_CXX_FLAGS" ${CMAKE_CXX_FLAGS})
MESSAGE("Boost_INCLUDE_DIRS:" ${Boost_INCLUDE_DIRS})
message("Boost_LIBRARY_DIRS:" ${Boost_LIBRARY_DIRS})
MESSAGE("Boost_SYSTEM_LIBRARY:" ${Boost_SYSTEM_LIBRARY})
message("Boost_LIBRARIES:" ${Boost_LIBRARIES})

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

aux_source_directory(. SRC)
message("SRC:" ${SRC})
add_executable(boost_asio01 ${SRC})

set(LIBRARIES ${Boost_LIBRARIES})
if(UNIX)
    list(APPEND LIBRARIES pthread)
    MESSAGE("LIBRARIES: " ${LIBRARIES})
endif()
target_link_libraries(boost_asio01 ${LIBRARIES})

