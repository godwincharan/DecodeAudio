cmake_minimum_required(VERSION 3.8)

set(Sources
    ${Sources}
    ${CMAKE_CURRENT_SOURCE_DIR}/ReaderFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WaveReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OggReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FlacReader.cpp
    PARENT_SCOPE
)
set(Headers
    ${Headers}
    ${CMAKE_CURRENT_SOURCE_DIR}/IReader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ReaderFactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WaveReader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OggReader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FlacReader.hpp
    PARENT_SCOPE
)