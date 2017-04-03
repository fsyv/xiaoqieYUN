#include"database.h"
#include<stdio.h>


DATABASE_INFO checkUserLogin(char* name, char* password)
{
	MYSQL con;

	int res;

	char query_name[60] = "select * from user_login where name=\"";

	char query_password[60] = "select * from user_login where password=\"";

	MYSQL_RES *res_ptr; /*指向查询结果的指针*/

	MYSQL_FIELD *field; /*字段结构指针*/

	MYSQL_ROW result_row; /*按行返回的查询信息*/

	int row, column; /*查询返回的行数和列数*/

	bool name_success = false;

	bool password_success = false;



	mysql_init(&con);

	if (mysql_real_connect(&con, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, 0) != NULL)
	{
		mysql_query(&con, "set names utf8");

		strcat(query_name, name);

		strcat(query_password, password);

		strcat(query_name, "\"");

		strcat(query_password, "\"");

		res = mysql_query(&con, query_name);

		if (res)
		{
			mysql_close(&con);
			printf("1");
			return SERVER_ERROR;
		}
		else
		{
			res_ptr = mysql_store_result(&con);

			if (res_ptr)
			{
				column = mysql_num_fields(res_ptr);
				row = mysql_num_rows(res_ptr);

				if (row != 1)
				{
					mysql_close(&con);
					printf("2");
					return NAME_ERROR;
					
				}
				else
					name_success = true;
			}
		}
		


		res = mysql_query(&con, query_password);

		if (res)
		{
			mysql_close(&con);
			printf("3");
			return SERVER_ERROR;
		}
		else
		{
			res_ptr = mysql_store_result(&con);

			if (res_ptr)
			{
				column = mysql_num_fields(res_ptr);
				row = mysql_num_rows(res_ptr);

				if (row != 1)
				{
					mysql_close(&con);
					printf("4");
					return PASSWORD_ERROR;

				}
				else
					password_success = true;
			}
		}

		if (name_success == true && password_success == true)
			return USER_LOGIN_SUCCESS;


	}
	else
	{
		mysql_close(&con);
		printf("5");
		return SERVER_ERROR;
	}
}
void main()
{
	DATABASE_INFO info;
	info = checkUserLogin("user001", "0");
	if (info == SERVER_ERROR)
		printf("SERVER_ERROR");
	if (info == NAME_ERROR)
		printf("NAME_ERROR");
	if (info == PASSWORD_ERROR)
		printf("PASSWORD_ERROR");
	if (info == USER_LOGIN_SUCCESS)
		printf("USER_LOGIN_SUCCESS");
}