cmake_minimum_required(VERSION 3.16)
project(algorithms)

set(CMAKE_CXX_STANDARD 17)

# add_subdirectory(test)

add_library(algorithms algorithms.cpp algorithms.hpp graph.cpp graph.hpp list.cpp list.hpp sort.cpp sort.hpp)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (algorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_exe test/main.cpp)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries (test_exe LINK_PUBLIC algorithms)