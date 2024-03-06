# Copyright (C) 2015-2023 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.8)

project(routingManager)
message(STATUS "VSOMEIP_NAME: " ${VSOMEIP_NAME})
message(STATUS "Boost_LIBRARIES: " ${Boost_LIBRARIES})
message(STATUS "DL_LIBRARY: " ${DL_LIBRARY})
message(STATUS "DLT_LIBRARIES: " ${DLT_LIBRARIES})
message(STATUS "CMAKE_THREAD_LIBS_INIT: " ${CMAKE_THREAD_LIBS_INIT})

set(DEPENDLIB 
    vsomeip3
    pthread
    boost_thread
    boost_system
    boost_log
)

# Daemon
add_executable(routingmanagerd routingmanagerd.cpp)
# target_link_libraries(routingmanagerd ${VSOMEIP_NAME} ${Boost_LIBRARIES} ${DL_LIBRARY} ${DLT_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(routingmanagerd
    ${DEPENDLIB}
)
if(${CMAKE_SYSTEM_NAME} MATCHES "QNX")
    target_link_libraries(routingmanagerd socket)
endif()
# add_dependencies(routingmanagerd ${VSOMEIP_NAME})

option(VSOMEIP_INSTALL_ROUTINGMANAGERD "Whether or not to install the routing manager daemon.")

if (VSOMEIP_INSTALL_ROUTINGMANAGERD)
    install (
        TARGETS routingmanagerd
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    )
endif()



###################################################################################################
