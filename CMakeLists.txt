cmake_minimum_required(VERSION 3.10)

project(Home-Simulation-Oops-Cpp)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES src/*.cpp)

add_executable(Home-Simulation-Oops-Cpp ${SRC_FILES})

target_include_directories(Home-Simulation-Oops-Cpp PRIVATE include)

target_compile_options(Home-Simulation-Oops-Cpp PRIVATE -Wall -Wextra)