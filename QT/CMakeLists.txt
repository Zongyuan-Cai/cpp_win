cmake_minimum_required(VERSION 3.16)
project(QtTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(QtTest main.cpp)
target_link_libraries(QtTest Qt6::Widgets)
