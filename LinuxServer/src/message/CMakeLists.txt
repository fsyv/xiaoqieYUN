set(NSTDMSGIO_HEAD_FILE nstdmsgio.h)
set(MSG_TYPE_HEAD_FILE msgType.h)
set(MSG_SOURCE_FILES msg.h msg.c)
set(RECVMSG_SOURCE_FILES recvMsg.h recvMsg.c)
set(SENDMSG_SOURCE_FILES sendMsg.h sendMsg.c)

link_libraries(socketQueue)
add_library(msgIO SHARED ${NSTDMSGIO_HEAD_FILE} ${MSG_TYPE_HEAD_FILE} ${MSG_SOURCE_FILES} ${RECVMSG_SOURCE_FILES} ${SENDMSG_SOURCE_FILES})

