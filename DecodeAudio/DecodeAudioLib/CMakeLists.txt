cmake_minimum_required(VERSION 3.8)

set(This DecodeAudioLib)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

include_directories(${DecodeAudio_SOURCE_DIR}/ThirdParty/dr_libs)
include_directories(${DecodeAudio_SOURCE_DIR}/DecodeAudio/Logger)

set(Headers
    DecodeAudio.hpp
)

add_subdirectory(AudioReader)
add_subdirectory(Decoder)

add_library(${This} STATIC ${Headers})
