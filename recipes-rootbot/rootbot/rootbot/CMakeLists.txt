cmake_minimum_required(VERSION 3.16)

project(rootbot)

add_executable(rootbot rootbot.cpp)

set_target_properties(rootbot PROPERTIES PUBLIC_HEADER rootbot.h)

install(TARGETS rootbot DESTINATION /home/root
        PUBLIC_HEADER DESTINATION include)
