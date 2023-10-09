cmake_minimum_required (VERSION 2.8)

project(boost_timer)

FIND_PACKAGE(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_PREFIX_INSTALL})
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

# link_directories(${Boost_LIBRARY_DIRS})

set(SRC sync_timer.cpp)
add_executable(boost_sync_timer ${SRC})
add_executable(boost_async_timer async_timer.cpp)
add_executable(boost_repeat_async_timer repeat_async_timer.cpp)
add_executable(boost_repeat_async_timer_memfunc repeat_async_timer_memfunc.cpp)


set(LIBRARIES ${Boost_LIBRARIES})
if(UNIX)
    list(APPEND LIBRARIES pthread)
    MESSAGE("LIBRARIES: " ${LIBRARIES})
endif()

target_link_libraries(boost_sync_timer ${LIBRARIES})
target_link_libraries(boost_async_timer ${LIBRARIES})
target_link_libraries(boost_repeat_async_timer ${LIBRARIES})
target_link_libraries(boost_repeat_async_timer_memfunc ${LIBRARIES})
