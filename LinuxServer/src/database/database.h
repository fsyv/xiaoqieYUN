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

//variable 
typedef enum _UserStatus
{	
	MYSQL_LOGIN_SUCCESS =  0,
	MYSQL_LOGIN_ERROR = 1, 
	MYSQL_REGISTER_SUCCESS = 2,
	MYSQL_REGISTER_ERROR = 3,
	MYSQL_CONN_ERROR
}UserStatus;


//MySQL handle
MYSQL mysql, *sock; 
MYSQL_RES *result;
MYSQL_ROW row;

UserStatus regis(const char *username, const char *password);
UserStatus login(const char *username, const char *password); 

#endif //DATABASE_H
