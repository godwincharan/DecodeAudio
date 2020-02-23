cmake_minimum_required(VERSION 3.8)

set(Sources
    ${Sources}
    ${CMAKE_CURRENT_SOURCE_DIR}/Decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BitStreamDecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StringDecoder.cpp
    PARENT_SCOPE
)
set(Headers
    ${Headers}
    ${CMAKE_CURRENT_SOURCE_DIR}/Decoder.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BitStreamDecoder.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StringDecoder.hpp
    PARENT_SCOPE
)