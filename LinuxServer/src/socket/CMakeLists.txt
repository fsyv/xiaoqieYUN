set(SERVERSOCKET_SOURCE_FILES serverSocket.h serverSocket.c)

link_libraries(msgIO)
add_library(serverSocket SHARED ${SERVERSOCKET_SOURCE_FILES})