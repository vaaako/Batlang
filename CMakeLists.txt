# cmake -S . -B build/
# cmake --build build/
# ./build/your_defined_name

cmake_minimum_required(VERSION 3.20)
project(bat)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp")
add_executable(bat src/main.cpp ${SOURCES}) # compiled name, main file
