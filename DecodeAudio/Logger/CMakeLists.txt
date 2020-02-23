cmake_minimum_required(VERSION 3.8)

set(This Logger)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

set(Headers
    Logger.hpp
)
set(Sources
    Logger.cpp
)
add_library(${This} STATIC ${Sources} ${Headers})