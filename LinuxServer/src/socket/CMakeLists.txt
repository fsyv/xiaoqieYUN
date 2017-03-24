set(SERVERSOCKET_SOURCE_FILES serverSocket.h serverSocket.c)

link_libraries(socketQueue)

add_library(serverSocket SHARED ${SERVERSOCKET_SOURCE_FILES})