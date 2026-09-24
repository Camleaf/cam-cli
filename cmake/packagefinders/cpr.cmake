
function(add_cpr_to_target_vcpkg targetname is_private)
    find_package(cpr CONFIG REQUIRED)
    if(is_private EQUAL TRUE)
        target_link_libraries(${targetname} PRIVATE cpr::cpr)
    else ()
        target_link_libraries(${targetname} PUBLIC cpr::cpr)
    endif ()
endfunction()

add_package_finder("cpr" "add_cpr_to_target_vcpkg")

