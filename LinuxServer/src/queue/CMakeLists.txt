set(QUEUE_SOURCE_FILES queue.h queue.c)
set(SOCKET_QUEUE_SOURCE_FILES socketQueue.h socketQueue.c)

add_library(queue SHARED ${QUEUE_SOURCE_FILES})

link_libraries(queue)
add_library(socketQueue SHARED ${SOCKET_QUEUE_SOURCE_FILES})