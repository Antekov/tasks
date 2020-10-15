cmake_minimum_required(VERSION 3.5)

project("geometry")

find_package(Catch2 REQUIRED)
add_executable(testExecutable tests/geometry_test.cpp)
target_link_libraries(testExecutable Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(testExecutable)