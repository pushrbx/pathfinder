# ------------------------------------------------------------------------------
# helpers
# ------------------------------------------------------------------------------

# define CMake designation of shared libraries (DLL or so) whatever the OS is
if( WIN32 )
    set( SHARED_LIB_TYPE RUNTIME ) # CMake considers Dlls as RUNTIME on Windows!
else()
    set( SHARED_LIB_TYPE LIBRARY )
endif()

# Install shared libraries depending on the build configuration and OS
function( install_shared )	# 3 arguments:
    # ARGV0 = target
    # ARGV1 = release install destination
    # ARGV2 = 1 for debug install (if available)
    # ARGV3 = suffix (optional)
    if( NOT CMAKE_CONFIGURATION_TYPES )
        install( TARGETS ${ARGV0} ${SHARED_LIB_TYPE} DESTINATION ${ARGV1}${ARGV3} )
    else()
        install( TARGETS ${ARGV0} ${SHARED_LIB_TYPE} CONFIGURATIONS Release DESTINATION ${ARGV1}${ARGV3} )
        install( TARGETS ${ARGV0} ${SHARED_LIB_TYPE} CONFIGURATIONS RelWithDebInfo DESTINATION ${ARGV1}_withDebInfo${ARGV3} )
        if (${ARGV2} EQUAL 1)
            install( TARGETS ${ARGV0} ${SHARED_LIB_TYPE} CONFIGURATIONS Debug DESTINATION ${ARGV1}_debug${ARGV3} )
        endif()
    endif()
endfunction()

# Copy files to the specified directory and for the active configurations
function( copy_files )	# 2 arguments:
    # ARGV0 = files (if it's a list you have to provide the list alias quoted!)
    # ARGV1 = target (directory)

    message(STATUS "Files " ${ARGV0} " will be installed to dest. " ${ARGV1})
    if( NOT CMAKE_CONFIGURATION_TYPES )
        install( FILES ${ARGV0} DESTINATION ${ARGV1} )
    else()
        install( FILES ${ARGV0} CONFIGURATIONS Release DESTINATION ${ARGV1} )
        install( FILES ${ARGV0} CONFIGURATIONS RelWithDebInfo DESTINATION ${ARGV1}_withDebInfo )
        install( FILES ${ARGV0} CONFIGURATIONS Debug DESTINATION ${ARGV1}_debug )
    endif()
endfunction()

# Extended 'install' command depending on the build configuration and OS
# 4 arguments:
#   - ARGV0 = signature
#   - ARGV1 = target (warning: one project or one file at a time)
#   - ARGV2 = base install destination (_debug or _withDebInfo will be automatically appended if multi-conf is supported)
#   - ARGV3 = install destination suffix (optional)
function( install_ext )
    if( NOT CMAKE_CONFIGURATION_TYPES )
        install( ${ARGV0} ${ARGV1} DESTINATION ${ARGV2}${ARGV3} )
    else()
        install( ${ARGV0} ${ARGV1} CONFIGURATIONS Release DESTINATION ${ARGV2}${ARGV3} )
        install( ${ARGV0} ${ARGV1} CONFIGURATIONS RelWithDebInfo DESTINATION ${ARGV2}_withDebInfo${ARGV3} )
        install( ${ARGV0} ${ARGV1} CONFIGURATIONS Debug DESTINATION ${ARGV2}_debug${ARGV3} )
    endif()
endfunction()

function ( setup_gtest )
    # ARGV0 - the project name

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include")
    endif()

    target_link_libraries(${ARGV0} gtest_main)
endfunction()