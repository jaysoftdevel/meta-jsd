cmake_minimum_required(VERSION 3.16)

project(rootbot)

set(CMAKE_CXX_STANDARD 11)  # Adjust the standard as needed

# Find the required package for nlohmann/json
find_package(nlohmann_json REQUIRED)

# Create an executable for your main program
add_executable(rootbot main.cpp Rootbot.cpp DistanceSensors.cpp ConnectionStatus.cpp MotorStatus.cpp)

# Link nlohmann/json to your executable
target_link_libraries(rootbot nlohmann_json::nlohmann_json)

# Disable optimization for GCC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

# Specify the header files to be installed
set(HEADERS
    Rootbot.hpp
    DistanceSensors.hpp
    ConnectionStatus.hpp
    MotorStatus.hpp
)

# Install the header files to a specific directory
install(FILES ${HEADERS} DESTINATION include)

# Install the executable
install(TARGETS rootbot DESTINATION /home/root)
