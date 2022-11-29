cmake_minimum_required(VERSION 2.8)

project(multiDirMultiFile_hello01)


add_subdirectory(hello)
aux_source_directory(. SRC)
message(-------------------status----------------- ${SRC})

add_executable(hello_by_static ${SRC})

target_link_libraries(hello_by_static helloFunc)