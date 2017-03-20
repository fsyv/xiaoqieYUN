set(SOCKET_QUEUE_SOURCE_FILES socketQueue.h socketQueue.c)

add_library(socketQueue SHARED ${SOCKET_QUEUE_SOURCE_FILES})

set(CLIENT_THREAD_POOL_QUEUE clientThreadPoolQueue.h clientThreadPoolQueue.c)

add_library(clientThreadPoolQueue SHARED ${CLIENT_THREAD_POOL_QUEUE})