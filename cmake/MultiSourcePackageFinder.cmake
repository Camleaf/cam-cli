
function(add_package_finder packagename target_append_fun_vcpkg_name)
    list(APPEND PACKAGE_NAMES ${packagename})
    list(APPEND PACKAGE_TARGET_APPEND_VCPKG_FUN ${target_append_fun_vcpkg_name})
    # Make the package names var not local scope
    set(PACKAGE_NAMES ${PACKAGE_NAMES} PARENT_SCOPE)
    set(PACKAGE_TARGET_APPEND_VCPKG_FUN ${PACKAGE_TARGET_APPEND_VCPKG_FUN} PARENT_SCOPE)
endfunction()

function(add_package_to_target packagename targetname is_private)
    list(FIND PACKAGE_NAMES ${packagename} index)
    if(index EQUAL -1)
        message(FATAL_ERROR "Failed to find ${packagename} in the list of register targets when trying to find it for target ${targetname}")
    endif ()
    list(GET PACKAGE_TARGET_APPEND_VCPKG_FUN ${index} VCPKG_FUN)
    cmake_language(CALL ${VCPKG_FUN} ${targetname} ${is_private})
endfunction()
