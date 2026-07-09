function(add_rapidfuzz_to_target_vcpkg targetname is_private)
    find_package(rapidfuzz CONFIG REQUIRED)
    if(is_private EQUAL TRUE)
        target_link_libraries(${targetname} PRIVATE rapidfuzz::rapidfuzz)
    else ()
        target_link_libraries(${targetname} PUBLIC rapidfuzz::rapidfuzz)
    endif ()
endfunction()

add_package_finder("rapidfuzz" "add_rapidfuzz_to_target_vcpkg")

