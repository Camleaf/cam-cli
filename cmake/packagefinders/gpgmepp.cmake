function(add_gpgmepp_to_target_vcpkg targetname is_private)
    find_package(Gpgmepp CONFIG REQUIRED)
    if(is_private EQUAL TRUE)
        target_link_libraries(${targetname} PRIVATE Gpgmepp)
    else ()
        target_link_libraries(${targetname} PUBLIC Gpgmepp)
    endif ()
endfunction()

add_package_finder("gpgmepp" "add_gpgmepp_to_target_vcpkg")

