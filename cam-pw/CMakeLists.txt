add_subdirectory(implementation)
target_include_directories(uclient-implementation PUBLIC include)

add_executable(cam-pw main.cpp)

target_link_libraries(cam-pw PRIVATE uclient-implementation)
add_package_to_target("cli11" "cam-pw" TRUE)
