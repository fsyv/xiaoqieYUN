set(NSTDMSGIO_HEAD_FILE nstdmsgio.h)
set(MSG_TYPE_HEAD_FILE msgType.h)
set(MSG_HEAD_FILE msg.h)
set(RECVMSG_SOURCE_FILES recvMsg.h recvMsg.c)
set(SENDMSG_SOURCE_FILES sendMsg.h sendMsg.c)

link_libraries(serverop)
add_library(msgIO STATIC ${NSTDMSGIO_HEAD_FILE} ${MSG_TYPE_HEAD_FILE} ${MSG_HEAD_FILE} ${RECVMSG_SOURCE_FILES} ${SENDMSG_SOURCE_FILES})

