set(DATABASE_SOURCE_FILES database.h database.c)
link_libraries(mysqlclient)
add_library(db SHARED ${DATABASE_SOURCE_FILES})