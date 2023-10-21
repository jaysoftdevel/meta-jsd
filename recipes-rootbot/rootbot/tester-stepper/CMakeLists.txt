cmake_minimum_required(VERSION 3.16)

project(tester-stepper)

add_executable(tester-stepper tester-stepper.cpp)

target_link_libraries(tester-stepper pthread)

install(TARGETS tester-stepper
        RUNTIME DESTINATION /home/root
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)