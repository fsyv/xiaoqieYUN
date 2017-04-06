set(SERVER_OPEARTING_SOURECE_FILES serverOperating.h serverOperating.c)

link_libraries(cjson)
link_libraries(msgIO)
add_library(serverop STATIC ${SERVER_OPEARTING_SOURECE_FILES})