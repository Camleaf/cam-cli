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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/cam-cli/)


# subdirs
add_subdirectory(src)

# add main executable
add_executable(cam-cli src/main.cpp)


#includes

target_link_libraries(cam-cli PRIVATE pw-man)
target_include_directories(cam-cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
