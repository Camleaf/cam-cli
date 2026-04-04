file(COPY
     "${CMAKE_SOURCE_DIR}/src/scripts" 
     DESTINATION "${assets_directory}"  
)

add_subdirectory(pw-man)
add_subdirectory(util)

