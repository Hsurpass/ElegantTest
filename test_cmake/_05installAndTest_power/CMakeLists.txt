# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo4)

# set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 是否使用自己的 MathFunctions 库
option(USE_MYMATH "Use provided math implementation" ON)
# option(USE_MYMATH "Use provided math implementation" OFF)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/config.h"
)

# 是否加入 MathFunctions 库
if(USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif()

# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(demo5 ${DIR_SRCS})

# 添加链接库
target_link_libraries(demo5 ${EXTRA_LIBS})

# 指定可执行程序和config.h安装路径
install(TARGETS demo5 DESTINATION ${PROJECT_SOURCE_DIR}/install/bin)
install(FILES config.h DESTINATION ${PROJECT_SOURCE_DIR}/install/include)


#启用测试
enable_testing()

#测试程序是否成功运行
add_test(test_run demo5 5 2)

# 测试帮助信息是否可以正常提示
add_test(test_usage demo5)
set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

#测试5的平方
add_test(NAME test_5_2 COMMAND demo5 5 2)
set_tests_properties(test_5_2 PROPERTIES PASS_REGULAR_EXPRESSION "is 25")

# 测试 2 的 10 次方
add_test (test_2_10 demo5 2 10)
set_tests_properties(test_2_10 PROPERTIES PASS_REGULAR_EXPRESSION "is 1024")


# 定义一个宏，用来简化测试工作
macro(do_test arg1 arg2 result)
    add_test(test_${arg1}_${arg2} demo5 ${arg1} ${arg2})
    set_tests_properties(test_${arg1}_${arg2} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)

# 利用 do_test 宏，测试一系列数据
do_test(2 3 "is 8")
do_test(2 4 "is 16")


