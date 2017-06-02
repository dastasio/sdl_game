cmake_minimum_required( VERSION 3.1)

project(sdl_game)
set( EXEC_NAME "tetris")

set( EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set( LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})
set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmodules")
set( mylib "${PROJECT_SOURCE_DIR}/code")

message( "system name: " ${CMAKE_SYSTEM})
message( "system processor: " ${CMAKE_SYSTEM_PROCESSOR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory( code)