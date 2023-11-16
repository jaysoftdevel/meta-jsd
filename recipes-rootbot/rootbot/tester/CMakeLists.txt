cmake_minimum_required(VERSION 3.16)

project(tester)

add_executable(tester tester.cpp)

#SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_BUILD_TYPE Debug)

target_link_libraries(tester pthread)

install(TARGETS tester
        RUNTIME DESTINATION /home/root
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)