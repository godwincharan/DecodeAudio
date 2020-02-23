cmake_minimum_required(VERSION 3.8)

set(This DecodeAudioLibTests)

include_directories(${DecodeAudio_SOURCE_DIR}/ThirdParty/dr_libs)
include_directories(${DecodeAudio_SOURCE_DIR}/DecodeAudio/DecodeAudioLib)
include_directories(${DecodeAudio_SOURCE_DIR}/DecodeAudio/Logger)

set(Sources
    DecodeAudioLibTests.cpp
)
add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    DecodeAudioLib
    Logger
)

add_test(
    NAME ${This}
    COMMAND ${This}
)

configure_file(${DecodeAudio_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_1.wav ${CMAKE_CURRENT_BINARY_DIR}/file_1.wav COPYONLY)
configure_file(${DecodeAudio_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_2.wav ${CMAKE_CURRENT_BINARY_DIR}/file_2.wav COPYONLY)
configure_file(${DecodeAudio_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_3.wav ${CMAKE_CURRENT_BINARY_DIR}/file_3.wav COPYONLY)

configure_file(${DecodeAudio_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_1_bit_stream.txt ${CMAKE_CURRENT_BINARY_DIR}/file_1_bit_stream.txt COPYONLY)
configure_file(${DecodeAudio_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_2_bit_stream.txt ${CMAKE_CURRENT_BINARY_DIR}/file_2_bit_stream.txt COPYONLY)
configure_file(${DecodeAudio_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_3_bit_stream.txt ${CMAKE_CURRENT_BINARY_DIR}/file_3_bit_stream.txt COPYONLY)

configure_file(${DecodeAudio_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_1_message.txt ${CMAKE_CURRENT_BINARY_DIR}/file_1_message.txt COPYONLY)
configure_file(${DecodeAudio_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_2_message.txt ${CMAKE_CURRENT_BINARY_DIR}/file_2_message.txt COPYONLY)
configure_file(${DecodeAudio_SOURCE_DIR}/ProblemStatement/Decoding_WaveFiles/file_3_message.txt ${CMAKE_CURRENT_BINARY_DIR}/file_3_message.txt COPYONLY)