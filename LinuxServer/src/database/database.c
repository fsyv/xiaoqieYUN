//
// Created by lz153 on 2017/4/14.
//

#include "database.h"
#include <string.h>
#include <stdio.h>
UserStatus regis(const char *username, const char *password)
{
    char sql[1024] = "select * from user where username = '";
    char sql2[1024] = "";
    mysql_init(&mysql);
    sock = mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0);
    if(!sock)
        return MYSQL_CONN_ERROR;

    strcat(sql, username);
    strcat(sql, "'");

    if(mysql_query(&mysql, sql))
    {
        return MYSQL_CONN_ERROR;
    }

    result = mysql_store_result(&mysql);

    if(mysql_num_rows(result))
        return MYSQL_REGISTER_ERROR;
    else
    {
        sprintf(sql2, "insert into user(username, userpassword) values('%s', '%s')", username, password);
//		printf("%s", sql2);
        if(mysql_query(&mysql, sql2))
        {
            return MYSQL_REGISTER_ERROR;
        }
        else
            return MYSQL_REGISTER_SUCCESS;
    }

}
UserStatus login(const char *username, const char *password)
{


}
