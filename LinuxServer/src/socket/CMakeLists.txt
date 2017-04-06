set(SERVERSOCKET_SOURCE_FILES serverSocket.h serverSocket.c)
set(SERVERFILESOCKET_SOURCE_FILES serverFileSocket.h serverFileSocket.c)

link_libraries(msgIO)
link_libraries(tools)
add_library(serverSocket STATIC ${SERVERSOCKET_SOURCE_FILES} ${SERVERFILESOCKET_SOURCE_FILES})