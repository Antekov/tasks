cmake_minimum_required(VERSION 3.8.0)
project(TaskA VERSION 0.1.0)

add_executable(TaskA src/taskA.cpp)
add_executable(TaskAtest tests/tests.cpp src/catch.cpp src/catch.hpp src/taskA.hpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(CTest)

