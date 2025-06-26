cmake_minimum_required(VERSION 3.16.3)

project(LabGearAutomation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/core/include/)

add_executable(main main.cpp)