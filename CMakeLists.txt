cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

project(cpp-robot)

add_executable(testColor test/testColor.cpp)
add_executable(testEventWriter test/testEventWriter.cpp)
add_executable(testRobot test/testRobot.cpp)
add_executable(testScreenReader test/testScreenReader.cpp)