cmake_minimum_required(VERSION 3.10)

project(i2c_test)

set(CMAKE_CXX_STANDARD 11)

add_library(i2c i2c.cpp i2c.h)
add_executable(i2c_test main.cpp)
target_link_libraries(i2c_test i2c)
