cmake_minimum_required(VERSION 3.28)

project(RationalGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

find_package(GTest REQUIRED)

add_executable(unit_tests)

target_sources(unit_tests
    PRIVATE
        main.cpp
        Rational.cpp
    PUBLIC
        FILE_SET CXX_MODULES FILES
        Rational.cppm
        Mixin.cppm
)

target_link_libraries(unit_tests PRIVATE GTest::gtest GTest::gtest_main)

target_compile_options(unit_tests PRIVATE -fmodules-ts -Wall -Wextra)

enable_testing()
include(GoogleTest)
gtest_discover_tests(unit_tests)
