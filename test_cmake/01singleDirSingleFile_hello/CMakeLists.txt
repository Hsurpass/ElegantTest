#linux: mkdir buildlinux && cd buildlinux && 
#        cmake .. && make (同cmake --build buildlinux(为了跨平台))
#win: cmake -B buildwin -G "Visual Studio 16 2019" 

# cmake最低版本号
cmake_minimum_required(VERSION 2.8)

# 工程名
project(01singleDirSingleFile_hello)

# 指定生成目标
add_executable(singleDirSingleFile_hello main.cpp)