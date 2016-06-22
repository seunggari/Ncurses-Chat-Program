/*
 * =====================================================================================
 *
 *       Filename:  mydb.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 06월 21일 11시 40분 55초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Seunghoon, Choi
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "mydb.h"

#define DB_HOST		"root"
#define DB_PW		"hot111"
#define DB_NAME		"chat"
#define DB_PORT		3306


void init_sql(MYSQL *sql)
{
	mysql_init(sql);

	if (!mysql_real_connect(sql, NULL, DB_HOST, DB_PW, DB_NAME, DB_PORT, (char*)NULL, 0)) {
		error_handling("mysql_connect() error");
	}
}

char* select_id_query(MYSQL *sql, char *id)
{
	char query[100];
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	sprintf(query, "select count(id) from user where id='%s'", id);
	
	if (mysql_query(sql, query) != 0) {
		error_handling("select_query() error");
	}

	res = mysql_store_result(sql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);

	if (strcmp(row[0], "1") == 0) {
		return "right";
	}

	else {
		return "false";
	}
}

char* select_pw_query(MYSQL *sql, char *id, char *pw)
{
	char query[100];
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	sprintf(query, "select pw from user where id='%s'", id);
	
	if (mysql_query(sql, query) != 0) {
		error_handling("select_query() error");
	}

	res = mysql_store_result(sql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);

	if (strcmp(row[0], pw) == 0) {
		return "right";
	}

	else {
		return "false";
	}

}

char* insert_query(MYSQL *sql, char *id, char *pw)
{
	char query[100];

	sprintf(query, "insert into user values ('%s', '%s')", id, pw);
	printf("query : %s\n", query);

	if (mysql_query(sql, query) != 0) {
		return "false";
	}

	return "right";
}
