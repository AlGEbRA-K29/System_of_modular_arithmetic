cmake_minimum_required(VERSION 3.17)
project(lab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
add_executable(lab main.cpp mod_bigint.h bigint.h helpers.h)