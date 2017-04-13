set(SERVERSOCKET_SOURCE_FILES serverSocket.h serverSocket.c)

link_libraries(msgIO)
link_libraries(tools)
add_library(serverSocket STATIC ${SERVERSOCKET_SOURCE_FILES})