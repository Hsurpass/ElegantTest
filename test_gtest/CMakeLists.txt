# cd build 
# ctest or make test or ./a,out

cmake_minimum_required (VERSION 2.8)

project(test_gtest_add)

find_package(GTest REQUIRED)
message("--------------- find gtest")
FIND_PACKAGE(Threads REQUIRED)

message("--------------- GTest_FOUND: " ${GTest_FOUND})
message("--------------- GTEST_INCLUDE_DIRS: " ${GTEST_INCLUDE_DIRS})
message("--------------- GTEST_LIBRARIES: " ${GTEST_LIBRARIES})     # GTest::gtest
message("--------------- GTEST_MAIN_LIBRARIES: " ${GTEST_MAIN_LIBRARIES})   # GTest::gtest_main
message("--------------- GTEST_BOTH_LIBRARIES: " ${GTEST_BOTH_LIBRARIES})   # GTest::gtestGTest::gtest_main
# message("--------------- GTest::gtest: " ${GTest::gtest})
# message("--------------- GTest::gtest_main: " ${GTest::gtest_main})





# include_directories(${GTEST_INCLUDE_DIRS})
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_PREFIX_INSTALL})
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})


# # aux_source_directory(. SRC)
set(SRC add.h unittest_add.cpp)
message("SRC: " ${SRC})
add_executable(test_gtest_add ${SRC})
# target_link_libraries(test_gtest_add GTest::gtest GTest::gtest_main)
target_link_libraries(test_gtest_add ${GTEST_LIBRARIES} pthread)
# target_link_libraries(test_gtest_add gtest pthread)

enable_testing()
add_test(test_gtest_add test_gtest_add)
