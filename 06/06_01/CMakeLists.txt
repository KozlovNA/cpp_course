cmake_minimum_required(VERSION 3.10)

project(RationalTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_program main.cpp Rational.cpp)

target_compile_options(my_program PRIVATE -Wall -Wextra -pedantic -fsanitize=address)

target_link_libraries(my_program PRIVATE -fsanitize=address)
