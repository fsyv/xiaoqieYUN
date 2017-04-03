set(SERVER_OPEARTING_SOURECE_FILES serverOperating.h serverOperating.c)

link_libraries(cjson)
add_library(serverop SHARED ${SERVER_OPEARTING_SOURECE_FILES})