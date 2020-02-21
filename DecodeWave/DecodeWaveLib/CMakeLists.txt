cmake_minimum_required(VERSION 3.8)

set(This DecodeWaveLib)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

include_directories(${DecodeWave_SOURCE_DIR}/ThirdParty/dr_libs)
include_directories(${DecodeWave_SOURCE_DIR}/DecodeWave/Logger)

set(Headers
    DecodeWave.hpp
)
set(Sources
    DecodeWave.cpp
)
add_subdirectory(AudioReader)

add_library(${This} STATIC ${Sources} ${Headers})
