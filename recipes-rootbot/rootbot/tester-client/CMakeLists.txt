cmake_minimum_required(VERSION 3.16)

project(tester_client)


list(APPEND CMAKE_CXX_FLAGS "-g")

add_executable(tester_client tester_client.cpp)

install(TARGETS tester_client)
