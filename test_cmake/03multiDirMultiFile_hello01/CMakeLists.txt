cmake_minimum_required(VERSION 2.8)

project(multiDirMultiFile_hello01)

# 静态库输出目录
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/staticlib)
# 动态库输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
# cmake在windows平台链接动态库错误
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    SET(BUILD_SHARED_LIBS TRUE)
endif()

# 可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_subdirectory(hello)

aux_source_directory(. SRC)
message(-------------------status----------------- ${SRC})

add_executable(hello_bin ${SRC})

target_link_libraries(hello_bin helloFunc)