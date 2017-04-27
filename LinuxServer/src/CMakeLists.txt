set(MAIN_SOURCE_FILES main.c database/database.h database/database.c database/tool.h database/tool.c)


add_subdirectory(database)
add_subdirectory(message)
add_subdirectory(queue)
add_subdirectory(socket)
add_subdirectory(tools)
add_subdirectory(cjson)
add_subdirectory(operating)

link_libraries(mysqlclient)
link_libraries(threadpool)
link_libraries(serverSocket)
add_executable(LinuxServer ${MAIN_SOURCE_FILES} database/database.h database/database.c database/tool.h database/tool.c)
