# Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# set(EXAMPLE_CONFIG_FILES
#     "../config/vsomeip.json"
#     "../config/vsomeip-local.json"
#     "../config/vsomeip-tcp-client.json"
#     "../config/vsomeip-tcp-service.json"
#     "../config/vsomeip-udp-client.json"
#     "../config/vsomeip-udp-service.json"
# )

# Examples
# add_executable(request-sample request-sample.cpp ${EXAMPLE_CONFIG_FILES})
# target_link_libraries(request-sample ${DEPENDLIB}})

# add_executable(response-sample response-sample.cpp ${EXAMPLE_CONFIG_FILES})
# target_link_libraries(response-sample ${DEPENDLIB}})

# add_executable(subscribe-sample subscribe-sample.cpp ${EXAMPLE_CONFIG_FILES})
# target_link_libraries(subscribe-sample ${DEPENDLIB}})

# add_executable(notify-sample notify-sample.cpp ${EXAMPLE_CONFIG_FILES})
# target_link_libraries(notify-sample ${DEPENDLIB}})

# add_dependencies(examples request-sample response-sample subscribe-sample notify-sample)

# install (
#     TARGETS request-sample response-sample subscribe-sample notify-sample
#     RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
# )

###################################################################################################

cmake_minimum_required(VERSION 3.12)

project(sample)

SET(CMAKE_BUILD_TYPE Debug)
message(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

find_package(Boost REQUIRED)
find_package(vsomeip3 REQUIRED)
# find_package(dl REQUIRED)

message(STATUS "{VSOMEIP_NAME}: " ${VSOMEIP_NAME})
message(STATUS "{Boost_LIBRARIES}: " ${Boost_LIBRARIES})
message(STATUS "{DL_LIBRARY}: " ${DL_LIBRARY})

set(DEPENDLIB 
    vsomeip3
    pthread
    boost_thread
    boost_system
    boost_log
)
add_executable(request-sample request-sample.cpp)
target_link_libraries(request-sample 
    ${DEPENDLIB}
)

add_executable(response-sample response-sample.cpp)
target_link_libraries(response-sample 
    ${DEPENDLIB}
)

add_executable(subscribe-sample subscribe-sample.cpp)
target_link_libraries(subscribe-sample 
    ${DEPENDLIB}
)

add_executable(notify-sample notify-sample.cpp)
target_link_libraries(notify-sample 
    ${DEPENDLIB}
)

