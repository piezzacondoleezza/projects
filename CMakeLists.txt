cmake_minimum_required(VERSION 3.0)

project(orderBook CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(main main.cpp)

add_library(lib proj.cpp)

target_link_libraries(main lib)