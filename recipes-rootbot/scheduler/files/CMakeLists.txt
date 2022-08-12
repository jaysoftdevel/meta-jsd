cmake_minimum_required(VERSION 3.16)

project(scheduler)

add_executable(scheduler main.cpp)

target_link_libraries(scheduler pthread)

install(TARGETS scheduler DESTINATION /home/root)
