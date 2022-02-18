cmake_minimum_required(VERSION 3.17)
project(lab)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab main.cpp mod_bigint.h bigint.h helpers.h)