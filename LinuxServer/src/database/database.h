#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

//database setting
#define HOST "localhost"
#define DATABASE "XQEY"
#define USER "root"
#define PASSWORD "123456"
#include "tool.h"
//variable 
typedef enum _UserStatus
{	
	MYSQL_LOGIN_SUCCESS =  0,
	MYSQL_LOGIN_ERROR = 1, 
	MYSQL_REGISTER_SUCCESS = 2,
	MYSQL_REGISTER_ERROR = 3,
	MYSQL_CONN_ERROR = 4,
	MYSQL_ADD_SUCCESS = 5,
        MYSQL_DEL_SUCCESS = 6,
        MYSQL_ADD_ERROR = 7,
        MYSQL_DEL_ERROR = 8,
	MYSQL_SEL_SUCCESS = 9,
	MYSQL_SEL_ERROR = 10
}UserStatus;


//MySQL handle
MYSQL mysql, *sock; 
MYSQL_RES *result;
//MYSQL_ROW row;

UserStatus regis(const char *username, const char *password);
UserStatus login(const char *username, const char *password); 
UserStatus addFileToDatabase(const char *username, const char *filename);
UserStatus delFileFromDatabase(const char *username, const char *filename);

//获取根据用户名和文件类型获取文件
char * selFileFromDtatbase(const char *username, TreeFileType filetype);


#endif //DATABASE_H
