cmake_minimum_required(VERSION 3.8)

set(This DecodeWaveTests)

set(Sources
    DecodeWaveTests.cpp
)
add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    DecodeWaveLib
)

add_test(
    NAME ${This}
    COMMAND ${This}
)