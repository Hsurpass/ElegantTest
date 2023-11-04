cmake_minimum_required (VERSION 3.10)

project(boost_daytime)

set(CMAKE_BUILD_TYPE Debug)

FIND_PACKAGE(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
message("boost found: " ${BOOST_FOUND})
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_PREFIX_INSTALL})
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

# link_directories(${Boost_LIBRARY_DIRS})

set(SRC sync_tcp_daytime_client.cpp)
add_executable(sync_tcp_daytime_client ${SRC})
add_executable(sync_tcp_daytime_server sync_tcp_daytime_server.cpp)
add_executable(async_tcp_daytime_server async_tcp_daytime_server.cpp)
add_executable(sync_udp_daytime_client sync_udp_daytime_client.cpp)
add_executable(sync_udp_daytime_server sync_udp_daytime_server.cpp)
# add_executable(async_udp_daytime_server async_udp_daytime_server.cpp)


set(LIBRARIES ${Boost_LIBRARIES})
if(UNIX)
    # list(APPEND LIBRARIES pthread)
    list(APPEND LIBRARIES pthread boost_system boost_thread)

    MESSAGE("LIBRARIES: " ${LIBRARIES} )
endif()

target_link_libraries(sync_tcp_daytime_client ${LIBRARIES})
target_link_libraries(sync_tcp_daytime_server ${LIBRARIES})
target_link_libraries(async_tcp_daytime_server ${LIBRARIES})
target_link_libraries(sync_udp_daytime_client ${LIBRARIES})
target_link_libraries(sync_udp_daytime_server ${LIBRARIES})
# target_link_libraries(async_udp_daytime_server ${LIBRARIES})

