#include <my_global.h>
#include <mysql.h>
#include <iostream>
#include <stdio.h>
#pragma comment(lib,"libmySQL.lib")
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "pnucse"
#define DB_NAME "test"
#define CHOP(x) x[strlen(x) - 1] = ' '

int main(void)
{
	MYSQL       *connection = NULL, conn;
	MYSQL_RES   *sql_result;
	MYSQL_ROW   sql_row;
	int       query_stat;

	char name[12];
	char address[80];
	char tel[12];
	char query[255];

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST,
		DB_USER, DB_PASS,
		DB_NAME, 3306,
		(char *)NULL, 0);

	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}

	query_stat = mysql_query(connection, "select * from login");
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);

	printf("ID 비밀번호\n");
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		printf("%s %s \n", sql_row[0], sql_row[1]);
	}

	mysql_free_result(sql_result);

	printf("Insert Value \n");
	printf("이름 :");
	fgets(name, 12, stdin);
	CHOP(name);

	printf("비밀번호 :");
	fgets(address, 80, stdin);
	CHOP(address);


	sprintf(query, "insert into login values "
		"('%s', '%s')",
		name, address);
	
	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	mysql_close(connection);
	// while(1) {}
}