cmake_minimum_required(VERSION 3.28)
project(RationalModules LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_executable(main)

target_sources(main
    PRIVATE
        main.cpp
        Rational.cpp
    PUBLIC
        FILE_SET CXX_MODULES FILES
        Rational.cppm
        Mixin.cppm
)

target_compile_options(main PRIVATE -fmodules-ts -Wall -Wextra)
