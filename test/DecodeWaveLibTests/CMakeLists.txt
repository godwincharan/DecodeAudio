cmake_minimum_required(VERSION 3.8)

set(This DecodeWaveLibTests)

include_directories(${DecodeWave_SOURCE_DIR}/ThirdParty/dr_libs-master)
include_directories(${DecodeWave_SOURCE_DIR}/DecodeWave/DecodeWaveLib)

set(Sources
    DecodeWaveLibTests.cpp
)
add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    DecodeWaveLib
    Logger
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
