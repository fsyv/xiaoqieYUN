//
// Created by lz153 on 2017/4/14.
//

#include "tool.h"
#include "database.h"
#include "../cjson/cJSON.h"
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
UserStatus regis(const char *username, const char *password)
{
    char sql[1024] = "select * from user where username = '";
    char sql2[1024] = "";
    mysql_init(&mysql);
    sock = mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0);
    if(!sock)
    {
       mysql_close(&mysql);
       return MYSQL_CONN_ERROR;
    }

    strcat(sql, username);
    strcat(sql, "'");

    if(mysql_query(&mysql, sql))
    {
	mysql_close(&mysql);
        return MYSQL_CONN_ERROR;
    }

    result = mysql_store_result(&mysql);

    if(mysql_num_rows(result))
    {  
	 mysql_close(&mysql);
	 return MYSQL_REGISTER_ERROR;
    }
    else
    {
        sprintf(sql2, "insert into user(username, userpassword) values('%s', '%s')", username, password);
//		printf("%s", sql2);
        if(mysql_query(&mysql, sql2))
        {
             mysql_close(&mysql);
	     return MYSQL_REGISTER_ERROR;
        }
        else
	{
       	    mysql_close(&mysql); 
	    return MYSQL_REGISTER_SUCCESS;
    	}
    }

}
UserStatus login(const char *username, const char *password)
{
        char sql[1024] = "";
        mysql_init(&mysql);
        sock = mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0);
        if(!sock)
        {
       		mysql_close(&mysql);
        	return MYSQL_CONN_ERROR;
        }
	
	sprintf(sql, "select * from user where username='%s' and userpassword='%s'", username, password);
	if (mysql_query(&mysql, sql))
	{
		mysql_close(&mysql);
		return MYSQL_CONN_ERROR;
	}
	else
	{
		result = mysql_store_result(&mysql);
		if(mysql_num_rows(result))
		{
			mysql_close(&mysql);
			return MYSQL_LOGIN_SUCCESS;
    		}
		else
		{
			mysql_close(&mysql);
			return MYSQL_LOGIN_ERROR;
		}
	}	
}
UserStatus addFileToDatabase(const char *username, const char *filename)
{
	TreeFileType fileType =  getFileType(filename);
	
	char sql[1024] = "";
	char sql2[1024] = "";
	mysql_init(&mysql);
	sock = mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0);
	if (!sock)
	{
		mysql_close(&mysql);
		return MYSQL_CONN_ERROR;
	}

	sprintf(sql, "select * from file where username='%s' and filepath='%s';", username, filename);
	
	printf("%s\n", sql);

	if (mysql_query(&mysql, sql))
	{
		printf("CONN_ERROR\n");
		mysql_close(&mysql);
		return MYSQL_CONN_ERROR;
	}

	result = mysql_store_result(&mysql);

	if (mysql_num_rows(result))
	{
		//文件已经存在
		printf("file exist\n");
		mysql_close(&mysql);
		return MYSQL_ADD_ERROR;
	}	
	else
	{
		sprintf(sql2, "insert into file(username, filetype, filepath) values('%s', '%d', '%s')", username, fileType, filename);
		if (mysql_query(&mysql, sql2))
		{
			printf("insert error\n");
			mysql_close(&mysql);
			return MYSQL_ADD_ERROR;
		}
		else
		{
			printf("insert success\n");
			mysql_close(&mysql);
			return MYSQL_ADD_SUCCESS;
		}
	}
}

UserStatus delFileFromDatabase(const char *username, const char *filename)
{
	TreeFileType fileType =  getFileType(filename);

        char sql[1024] = "";
        char sql2[1024] = "";
        mysql_init(&mysql);
        sock = mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0);
        if (!sock)
        {
                mysql_close(&mysql);
                return MYSQL_CONN_ERROR;
        }

        sprintf(sql, "delete from file where username='%s' and filepath='%s';", username, filename);

        printf("%s\n", sql);

        if (mysql_query(&mysql, sql))
        {
                printf("CONN_ERROR\n");
                mysql_close(&mysql);
                return MYSQL_DEL_ERROR;
        }
	else
	{
		printf("DEL_SUCCESS");
		mysql_close(&mysql);
		return MYSQL_DEL_SUCCESS;
	}
}

char * selFileFromDtatbase(const char *username, TreeFileType filetype)
{
	char select[1024];
	int row;
	char info[9]="filelist";
	struct stat statBuf;
        cJSON *pRoot = cJSON_CreateObject();
        cJSON *pArray = cJSON_CreateArray();
	cJSON_AddItemToObject(pRoot, info, pArray);
	cJSON *pItem = NULL;

	MYSQL_ROW mysql_row;
	sprintf(select, "select filepath from file where username='%s' and filetype='%d';", username, filetype);

	printf("%s\n", select);	
	
	mysql_init(&mysql);
        sock = mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0);
        if (!sock)
        {
                mysql_close(&mysql);
                return NULL;
        }

//	开始查询
	if (mysql_query(&mysql, select))
        {
//	查询失败
                mysql_close(&mysql);
                return NULL;
        }

//获取结果集， 并且转换成 json
	result = mysql_store_result(&mysql);
	
	if (mysql_num_rows(result))
	{	
		while ((mysql_row = mysql_fetch_row(result))) 
		{
			stat(mysql_row[0], &statBuf);
   			pItem = cJSON_CreateObject();
    			cJSON_AddStringToObject(pItem, "name", mysql_row[0]);
    			printf("%s\n", mysql_row[0]);
			cJSON_AddStringToObject(pItem, "type", "file");
    			cJSON_AddNumberToObject(pItem, "lastmodifytime", statBuf.st_mtim.tv_sec);
    			printf("%ld\n", statBuf.st_mtim.tv_sec);
			cJSON_AddNumberToObject(pItem, "size", statBuf.st_size);
    			cJSON_AddItemToArray(pArray, pItem);
  	  	} 
	}
	else
	{
		printf("数据库无内容\n");
	}
	char* szOut = cJSON_PrintUnformatted(pRoot);
    	cJSON_Delete(pRoot);
	return szOut;
}
