cmake_minimum_required(VERSION 2.8)

project(SingleDirMultiFile_Hello)

# add_executable(singleDirMultiFile_hello main.cpp hello.cpp)

aux_source_directory(. SRC)
add_executable(singleDirMultiFile_hello ${SRC})