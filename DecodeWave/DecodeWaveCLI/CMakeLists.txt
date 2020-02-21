cmake_minimum_required(VERSION 3.8)

set(This DecodeWave)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

include_directories(${DecodeWave_SOURCE_DIR}/ThirdParty/dr_libs)
include_directories(${DecodeWave_SOURCE_DIR}/DecodeWave/DecodeWaveLib)

set(Sources
    main.cpp
)
add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    DecodeWaveLib
    Logger
)
