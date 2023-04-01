cmake_minimum_required(VERSION 3.16)

project(hcsr04-gpio)

add_executable(hcsr04-gpio main.cpp)

target_link_libraries(hcsr04-gpio libiofunc.a)

install(TARGETS hcsr04-gpio DESTINATION /home/root)
