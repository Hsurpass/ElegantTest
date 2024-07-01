cmake_minimum_required(VERSION 3.15)
project(my_project)

set(CMAKE_CXX_STANDARD 17)

# 引入 Conan 生成的文件
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# 添加可执行文件
add_executable(my_project src/main.cpp)

# 链接依赖库
target_link_libraries(my_project ${CONAN_LIBS})
