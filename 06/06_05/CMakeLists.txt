cmake_minimum_required(VERSION 3.10)
project(DynamicLoaderExample)

set(CMAKE_CXX_STANDARD 20) 

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED COMPONENTS filesystem system)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(plugin_v1 SHARED source/plugin_v1.cpp)
target_link_libraries(plugin_v1 Boost::filesystem Boost::system)

add_library(plugin_v2 SHARED source/plugin_v2.cpp)
target_link_libraries(plugin_v2 Boost::filesystem Boost::system)

add_executable(main source/main.cpp)
target_link_libraries(main ${CMAKE_DL_LIBS} Boost::filesystem Boost::system)

set_target_properties(main PROPERTIES ENABLE_EXPORTS ON)
