set(SERVERSOCKET_SOURCE_FILES serverSocket.h serverSocket.c)

add_library(serverSocket SHARED ${SERVERSOCKET_SOURCE_FILES})