cmake_minimum_required(VERSION 3.6)
project(LinuxServer)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

message(STATUS "This is LinuxServer Project")

add_subdirectory(src)
add_subdirectory(bin)