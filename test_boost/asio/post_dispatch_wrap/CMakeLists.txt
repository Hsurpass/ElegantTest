cmake_minimum_required (VERSION 3.10)

project(post_dispatch_wrap_strand)

set(CMAKE_BUILD_TYPE Debug)

FIND_PACKAGE(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
message("boost found: " ${BOOST_FOUND})
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_PREFIX_INSTALL})
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

# link_directories(${Boost_LIBRARY_DIRS})

set(SRC post.cpp)
add_executable(post ${SRC})
add_executable(strand strand.cpp)
add_executable(dispatch dispatch.cpp)
add_executable(wrap wrap.cpp)


set(LIBRARIES ${Boost_LIBRARIES})
if(UNIX)
    # list(APPEND LIBRARIES pthread)
    list(APPEND LIBRARIES pthread boost_system boost_thread)

    MESSAGE("LIBRARIES: " ${LIBRARIES} )
endif()

target_link_libraries(post ${LIBRARIES})
target_link_libraries(strand ${LIBRARIES})
target_link_libraries(dispatch ${LIBRARIES})
target_link_libraries(wrap ${LIBRARIES})

