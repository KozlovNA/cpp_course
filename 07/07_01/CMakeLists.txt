cmake_minimum_required(VERSION 3.14)
project(QuadraticSolver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(solver_lib src/solver.cpp)
target_include_directories(solver_lib PUBLIC include)

add_executable(solver_app src/main.cpp)
target_link_libraries(solver_app PRIVATE solver_lib)

find_package(GTest REQUIRED)

add_executable(run_tests tests/tests.cpp)

target_link_libraries(run_tests PRIVATE GTest::gtest_main solver_lib)
