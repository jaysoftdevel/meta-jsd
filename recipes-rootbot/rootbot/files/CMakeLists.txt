cmake_minimum_required(VERSION 3.16)

project(rootbot)

add_executable(tester tester.cpp)
add_executable(rootbot rootbot.cpp rootbot.h)
add_executable(tester_client test_client.cpp)

target_link_libraries(tester pthread)
target_link_libraries(rootbot pthread)

install(TARGETS rootbot DESTINATION /home/root)
install(TARGETS tester DESTINATION /home/root)
