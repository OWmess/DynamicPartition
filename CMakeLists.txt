cmake_minimum_required(VERSION 3.22)
project(DynamicParition)
set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)

add_executable(${PROJECT_NAME} main.cpp OS.cpp)

target_link_libraries(${PROJECT_NAME} fmt::fmt)