cmake_minimum_required(VERSION 3.12)
set( CMAKE_CXX_STANDARD 14 )

add_executable( crc source.cpp crc.hpp )

add_executable( test test.cpp )