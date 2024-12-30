cmake_minimum_required(VERSION 3.16)

project(tester-target-arch)

add_executable(tester-target-arch main.cpp)

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_BUILD_TYPE Debug)

# Check if the QEMU_MACHINE environment variable is set
set(ENV_QEMU_MACHINE $ENV{QEMU_MACHINE})
set(ENV_MACHINE $ENV{MACHINE})
set(ENV_CMAKE_SYSTEM_PROCESSOR $ENV{CMAKE_SYSTEM_PROCESSOR})
message(STATUS "### $ENV{QEMU_MACHINE} # $ENV{MACHINE} # $ENV{CMAKE_SYSTEM_PROCESSOR} ##")
if(ENV{MACHINE} STREQUAL "qemuarm")
    message("### Running build for QEMU")
    add_compile_definitions(QEMU_TARGET)
# elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
#     message("### Running build for ARM")
#     add_compile_definitions(ARM_TARGET)
else()
    message("### Unknown target architecture")
endif()

install(TARGETS tester-target-arch
        RUNTIME DESTINATION /home/root
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)