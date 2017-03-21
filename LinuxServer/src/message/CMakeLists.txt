set(MSG_TYPE_SOURCE msgType.h)
set(MSG_SOURCE msg.h msg.c)

add_library(msg SHARED ${MSG_TYPE_SOURCE} ${MSG_SOURCE})