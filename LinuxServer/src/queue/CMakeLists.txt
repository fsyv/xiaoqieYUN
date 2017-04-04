set(THREAD_POOL_SOURCE_FILES threadPool.h threadPool.c)

link_libraries(pthread)
add_library(threadpool SHARED ${THREAD_POOL_SOURCE_FILES})