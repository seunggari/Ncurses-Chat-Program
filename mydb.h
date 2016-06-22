/*
 * =====================================================================================
 *
 *       Filename:  mydb.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 06월 21일 11시 39분 47초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Seunghoon, Choi
 *   Organization:  
 *
 * =====================================================================================
 */

#ifdef MYDB_H
#define MYDB_H

void init_sql(MYSQL *sql);
char* select_id_query(MYSQL *sql, char *pw);
char* select_pw_query(MYSQL *sql, char *id, char *pw);
char* insert_query(MYSQL *sql, char *id, char *pw);

#endif
