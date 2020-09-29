cmake_minimum_required(VERSION 3.10)

project(Nova VERSION 0.1) 

configure_file(config.h.in config.h)

target_include_directories(Nova  PUBLIC "${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS " -Wall -g ")
include_directories(${PROJECT_SOURCE_DIR})

add_executable(Nova *.cxx)

