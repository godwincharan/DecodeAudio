cmake_minimum_required(VERSION 3.8)

set(This DecodeAudio)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

enable_testing()

add_subdirectory(ThirdParty)
add_subdirectory(DecodeAudio)
add_subdirectory(test)