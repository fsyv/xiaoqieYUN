set(MAIN_SOURCE_FILES main.c)

add_subdirectory(message)
add_subdirectory(queue)
add_subdirectory(socket)
add_subdirectory(tools)
add_subdirectory(cjson)
add_subdirectory(operating)
#add_subdirectory(database)

link_libraries(threadpool)
link_libraries(serverSocket)
add_executable(LinuxServer ${MAIN_SOURCE_FILES})