cmake_minimum_required(VERSION 2.8)

project(hello)

set(SRC main.cpp)

# include_directories(./include)
# link_directories(./lib)
# add_executable(${PROJECT_NAME} ${SRC})
# target_link_libraries(${PROJECT_NAME} Hello)


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/lib/cmake/Hello)
find_package(Hello REQUIRED)
# find_package(Hello REQUIRED MODULE)
message("Hello_FOUND: " ${Hello_FOUND})
message("Hello_INCLUDE_DIRS: " ${Hello_INCLUDE_DIRS})
message("Hello_LIBRARIES: " ${Hello_LIBRARIES})

include_directories(${Hello_INCLUDE_DIRS})
# link_directories(${Hello_})
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${Hello_LIBRARIES})
