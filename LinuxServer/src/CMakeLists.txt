set(MAIN_SOURCE_FILES main.c)

add_subdirectory(message)
add_subdirectory(queue)
add_subdirectory(socket)
add_subdirectory(tools)

set(NSTDMSGIO_HEAD_FILE ./message/nstdmsgio.h)
set(MSG_TYPE_HEAD_FILE ./message/msgType.h)
set(MSG_HEAD_FILE ./message/msg.h)
set(RECVMSG_SOURCE_FILES ./message/recvMsg.h ./message/recvMsg.c)
set(SENDMSG_SOURCE_FILES ./message/sendMsg.h ./message/sendMsg.c)
set(MESSAGE ${NSTDMSGIO_HEAD_FILE} ${MSG_TYPE_HEAD_FILE} ${MSG_HEAD_FILE} ${RECVMSG_SOURCE_FILES} ${SENDMSG_SOURCE_FILES})

set(CLIENT_THREAD_POOL_QUEUE ./queue/clientThreadPoolQueue.h ./queue/clientThreadPoolQueue.c)
set(QUEUE ${CLIENT_THREAD_POOL_QUEUE})

set(SERVERSOCKET_SOURCE_FILES ./socket/serverSocket.h ./socket/serverSocket.c)
set(SOCKET ${SERVERSOCKET_SOURCE_FILES})

set(TOOLS_SOURCE_FILES ./tools/tools.h ./tools/tools.c)
set(TOOLS ${TOOLS_SOURCE_FILES})

add_executable(LinuxServer ${MESSAGE} ${QUEUE} ${SOCKET} ${TOOLS})