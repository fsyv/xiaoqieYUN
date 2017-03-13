set(MAIN_SOURCE_FILES main.c)

add_executable(LinuxServer ${MAIN_SOURCE_FILES})

add_subdirectory(queue)
add_subdirectory(socket)