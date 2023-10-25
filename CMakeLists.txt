# cmake -S . -B build/
# cmake --build build/
# ./build/your_defined_name

cmake_minimum_required(VERSION 3.20)
project(Batlang)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES src/*.cpp)
add_executable(batlang ${SOURCES}) # Args: Compiled name, main file


# Create a variable to accumulate libraries
set(LDLIBS "")

# Append each library you want to link
list(APPEND LDLIBS editline)

# Link the libeditline library to your executable
target_link_libraries(batlang ${LDLIBS})
