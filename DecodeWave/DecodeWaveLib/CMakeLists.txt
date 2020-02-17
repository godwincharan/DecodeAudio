cmake_minimum_required(VERSION 3.8)

set(This DecodeWaveLib)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

set(Headers
DecodeWave.hpp
)
set(Sources
    DecodeWave.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})