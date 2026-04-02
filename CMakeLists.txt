cmake_minimum_required(VERSION 3.25)

# project definition
project(leaf 
    VERSION 0.1.0 
    LANGUAGES CXX
)

# c++ settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# for intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# for output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# subdirs
add_subdirectory(src)




# add main executable
add_executable(cam-cli main.cpp)
