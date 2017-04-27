set(DATABASE_SOURCE_FILES tool.h tool.c database.h database.c)
link_libraries(mysqlclient)
add_library(db SHARED ${DATABASE_SOURCE_FILES})
