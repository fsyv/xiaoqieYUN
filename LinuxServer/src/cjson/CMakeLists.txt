set(CJSON_SOURCE_FILES cJSON.h cJSON.c)

link_libraries(m)
add_library(cjson SHARED ${CJSON_SOURCE_FILES})

