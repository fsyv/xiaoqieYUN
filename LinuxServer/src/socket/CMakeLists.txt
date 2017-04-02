set(SERVERSOCKET_SOURCE_FILES serverSocket.h serverSocket.c)

link_libraries(msgIO)
link_libraries(tools)
add_library(serverSocket SHARED ${SERVERSOCKET_SOURCE_FILES})