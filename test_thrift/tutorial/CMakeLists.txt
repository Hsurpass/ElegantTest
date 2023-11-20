cmake_minimum_required(VERSION 3.1)

project(thriftTutorial)

find_package(Thrift REQUIRED)

message("Thrift_FOUND: " ${Thrift_FOUND})
message("THRIFT_COMPILER: " ${THRIFT_COMPILER})
message("THRIFT_INCLUDE_DIR: " ${THRIFT_INCLUDE_DIR})
message("CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})
message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
# message("CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})
# message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
# message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
# message("THRIFT_ROOT: " ${THRIFT_ROOT})
# message("THRIFT_HOME: " ${THRIFT_HOME})
# message("THRIFT_COMPILER_EXECUTABLE: " ${THRIFT_COMPILER_EXECUTABLE})
# message("THRIFT_CPP_LIBRARY: " ${Thrift_CPP_LIBRARY})


# set(thrift_gencpp_dir "${PROJECT_SOURCE_DIR}/gen-cpp")
# set(thrift_gencpp_srcs 
#     ${thrift_gencpp_dir}/Calculator.cpp
#     ${thrift_gencpp_dir}/SharedService.cpp 
#     ${thrift_gencpp_dir}/shared_types.cpp 
#     ${thrift_gencpp_dir}/tutorial_constants.cpp 
#     ${thrift_gencpp_dir}/tutorial_types.cpp
# )

# add_custom_command(
    #     OUTPUT ${thrift_gencpp_srcs}
    #     COMMAND ${THRIFT_COMPILER}
    #     ARGS -r --gen cpp -o ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/tutorial.thrift
    #     DEPENDS tutorial.thrift 
    #     WORKING_DIRECTORY  "."
# )
    
################使用EXECUTE_PROCESS 生成 文件#########################
EXECUTE_PROCESS(
    COMMAND bash compile.sh
    WORKING_DIRECTORY .
    OUTPUT_VARIABLE OUT
    RESULT_VARIABLE RET
)
message("EXECUTE_PROCESS tutorial Output val is: ${OUT}, return val: ${RET} ")

# 获取当前目录下的所有文件名  
file(GLOB thrift_gencpp_srcs "gen-cpp/*.cpp")
foreach(FILE ${thrift_gencpp_srcs})
    message(STATUS "${FILE}")  
endforeach()
    
# list(FILTER thrift_gencpp_srcs EXCLUDE REGEX ".skeleton.cpp$")  #删除所有以.skeleton.cpp结尾的元素
list(FILTER thrift_gencpp_srcs EXCLUDE REGEX "skeleton.cpp*")  #删除所有以.skeleton.cpp结尾的元素

# 遍历文件列表 删除元素
# foreach(FILE ${thrift_gencpp_srcs})
#     # message(STATUS "${FILE}")  
    
#     # 检查文件名是否为"*.skeleton.cpp"  
#     # if(NOT "${FILE}" STREQUAL "Calculator_server.skeleton.cpp")  
#     # if(${FILE} STREQUAL "Calculator_server.skeleton.cpp")  
    
#     string(FIND ${FILE} "Calculator_server.skeleton.cpp" pos REVERSE)   # 找到匹配的子串
#     MESSAGE(STATUS "pos: " ${pos})  # 位置
#     # IF(${pos} GREATER 0)
#     IF(NOT ${pos} EQUAL -1)
#         message(STATUS "${FILE}")   
#         string(SUBSTRING ${FILE} ${pos} -1 substring)   #获取字串
#         message(STATUS "substring: " ${substring})
#         list(REMOVE_ITEM thrift_gencpp_srcs ${FILE})    # right
#     endif()  
# endforeach()

message("-------------------------")
foreach(FILE ${thrift_gencpp_srcs})
    message(STATUS "${FILE}")  
endforeach()



    
add_library(tutorialgencpp STATIC ${thrift_gencpp_srcs})
target_link_libraries(tutorialgencpp thrift)

include_directories(${thrift_gencpp_dir})
add_executable(tutorialServer server.cpp ${thrift_gencpp_srcs})

# target_link_libraries(TutorialServer tutorialgencpp)


if (CMAKE_BUILD_TYPE STREQUAL "Debug") 
    message("debug")
    target_link_libraries(tutorialServer thriftd)

else(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("release")
    target_link_libraries(tutorialServer thriftd)
endif()





