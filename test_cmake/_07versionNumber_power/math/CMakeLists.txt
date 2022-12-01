# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 指定生成 MathFunctions 链接库
add_library (MathFunctions ${DIR_LIB_SRCS})

# 指定 MathFunctions 库的安装路径
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin)
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

install(TARGETS MathFunctions DESTINATION ${PROJECT_SOURCE_DIR}/install/bin)
install(FILES MathFunctions.h DESTINATION ${PROJECT_SOURCE_DIR}/install/include)

