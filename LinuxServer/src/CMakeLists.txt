set(MAIN_SOURCE_FILES main.c)


add_subdirectory(queue)
add_subdirectory(socket)

link_libraries(serverSocket)
add_executable(LinuxServer ${MAIN_SOURCE_FILES})