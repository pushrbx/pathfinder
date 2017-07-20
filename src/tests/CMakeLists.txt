cmake_minimum_required(VERSION 3.7)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../pathfinder)

project (pathfinderTests)

file(GLOB SOURCE_FILES "main.cpp" "*.cc")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )
add_dependencies( ${PROJECT_NAME} libpathfinder )

setup_gtest( ${PROJECT_NAME} )
target_link_libraries(${PROJECT_NAME} libpathfinder)
target_link_libraries(${PROJECT_NAME} GTest::main)
target_link_libraries(${PROJECT_NAME} GTest::gtest)

if (UNIX OR MINGW)
    # override the root cmakelists
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,--enable-auto-import -Wl,--exclude-all-symbols")
endif()

add_test(NAME pathfinder_gtest COMMAND pathfinderTests)
