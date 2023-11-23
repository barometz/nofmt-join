cmake_minimum_required(VERSION 3.5)
project(nofmt-join)

set(CMAKE_CXX_STANDARD 20)

add_library(nofmt-join INTERFACE nofmt/join.h)
set_target_properties(nofmt-join PROPERTIES PUBLIC_HEADER nofmt/join.h)

add_executable(nofmt-join-test main.cpp)
target_link_libraries(nofmt-join-test nofmt-join)
