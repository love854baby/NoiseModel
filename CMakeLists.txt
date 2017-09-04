cmake_minimum_required(VERSION 3.6)
project(NoiseModel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(NoiseModel ${SOURCE_FILES})

target_link_libraries(NoiseModel m)