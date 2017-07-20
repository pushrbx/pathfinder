cmake_minimum_required(VERSION 3.7)

cmake_policy(PUSH)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.36.tar.gz"
    SHA1 "db6f5483795c56968fe628b3cc9791ec6627bdfc"
)

if (APPLE)
    # see: https://cmake.org/Wiki/CMake_RPATH_handling
    set( CMAKE_SKIP_BUILD_RPATH  FALSE )
    set( CMAKE_BUILD_WITH_INSTALL_RPATH FALSE )
    set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )
endif()

include ("cmake/CMakePolicies.cmake")

project(pathfinder)

include("cmake/CMakeInclude.cmake")

include("cmake/CMakeSetCompilerOptions.cmake")

# Default debug suffix for libraries.
set( CMAKE_DEBUG_POSTFIX "d" )

# One shouldn't generate the BUILD project directly in the SOURCES folder!
if ( ${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    if ( NOT SAME_BUILD_AND_SOURCE_FOLDER_WARNING_ALREADY_ISSUED )
        message(FATAL_ERROR "It is not advised to BUILD the binaries directly in the SOURCE folder!\n If you want to proceed with this option, just CONFIGURE the project once again" )
        set( SAME_BUILD_AND_SOURCE_FOLDER_WARNING_ALREADY_ISSUED TRUE )
    endif()
endif()

# Default install folders
# (on Windows - msvc generator - the '_debug' suffix is automatically added for debug configurations)
set( INSTALL_DESTINATIONS pathfinder pathfinderTests)

# RPATH Linux/Unix: (dynamic) libs are put in a subdir of prefix/lib.
if( UNIX AND NOT APPLE )
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/libpathfinder")
endif()

include("cmake/CMakeSetCompilerOptions.cmake")

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory("src/pathfinder")

add_subdirectory("src/tests")

cmake_policy(POP)