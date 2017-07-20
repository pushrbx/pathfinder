cmake_minimum_required(VERSION 3.7)

project(libpathfinder)

file(GLOB SOURCE_FILES
        "*.h"
        "*.cpp")

hunter_add_package(Protobuf)
find_package(Protobuf CONFIG REQUIRED)

option(DEBUG_BUILD "1 if this is going to be a debug build, 0 otherwise." 1)
add_definitions(-D_DEBUG=${DEBUG_BUILD})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set_target_properties( ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "libpathfinder" )

if (WIN32)
    set_target_properties( ${PROJECT_NAME} PROPERTIES SUFFIX ".dll" )
endif()

if (UNIX OR MINGW)
    set_target_properties( ${PROJECT_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1 )
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

    # override the root cmakelists
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
    if (WIN32 AND MINGW)
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++ -Wl,--exclude-all-symbols")
    endif()
endif()

if (WIN32)
    set_property( TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS )
endif()

target_link_libraries(${PROJECT_NAME} protobuf::libprotobuf)
