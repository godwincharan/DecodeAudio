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

configure_file(${DecodeWave_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_1.wav ${CMAKE_CURRENT_BINARY_DIR}/file_1.wav COPYONLY)
configure_file(${DecodeWave_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_2.wav ${CMAKE_CURRENT_BINARY_DIR}/file_2.wav COPYONLY)
configure_file(${DecodeWave_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_3.wav ${CMAKE_CURRENT_BINARY_DIR}/file_3.wav COPYONLY)

configure_file(${DecodeWave_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_1_bit_stream.txt ${CMAKE_CURRENT_BINARY_DIR}/file_1_bit_stream.txt COPYONLY)
configure_file(${DecodeWave_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_2_bit_stream.txt ${CMAKE_CURRENT_BINARY_DIR}/file_2_bit_stream.txt COPYONLY)
configure_file(${DecodeWave_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_3_bit_stream.txt ${CMAKE_CURRENT_BINARY_DIR}/file_3_bit_stream.txt COPYONLY)

configure_file(${DecodeWave_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_1_message.txt ${CMAKE_CURRENT_BINARY_DIR}/file_1_message.txt COPYONLY)
configure_file(${DecodeWave_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_2_message.txt ${CMAKE_CURRENT_BINARY_DIR}/file_2_message.txt COPYONLY)
configure_file(${DecodeWave_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_3_message.txt ${CMAKE_CURRENT_BINARY_DIR}/file_3_message.txt COPYONLY)
