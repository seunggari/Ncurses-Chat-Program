/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 06월 17일 14시 02분 41초
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
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <ncurses.h>
#include <pthread.h>

#include "serversocket.h"
#include "mydb.h"
#define BUFSIZE 500

void* clnt_connection(void *arg);
void* draw_menu(void *arg);

MYSQL sql;
MYSQL *res;
MYSQL_ROW row;

pthread_mutex_t mutx;

int main(int argc, char **argv)
{
	Client *clnt = (Client*)malloc(sizeof(Client));
	pthread_t connect_thread, draw_thread;
	
	
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if (pthread_mutex_init(&mutx, NULL)) {
		error_handling("mutex init() error");
	}

	init_sql(&sql);

	printf("before : %s\n", select_query(&sql, "aa"));
	//insert_query(&sql, "cc", "ccc");

	init_serv_sock(argv[1]);
	printf("Waiting...\n");

	while(1) {

		clnt = connect_client();

		if (clnt->sock == -1) {
			continue;
		}

		pthread_create(&connect_thread, NULL, clnt_connection, (void*) clnt);
		//pthread_create(&draw_thread, NULL, draw_thread, (void*)NULL);
	}

	return 0;
}

void* clnt_connection(void *arg)
{
	char msg[BUFSIZE];
	Client *clnt = (Client*) arg;

	//init_sql(&sql);
	printf("after : %s\n", select_query(&sql, "aa"));

	printf("Connect!!\tIP : %s\n", inet_ntoa(clnt->sock_addr.sin_addr));

	while(1) {

		if (clnt->state == 0) {
			read(clnt->sock, msg, sizeof(msg));
			clnt->state = atof(msg);
		}

		if (clnt->state == 1) {
			read(clnt->sock, msg, sizeof(msg));

			pthread_mutex_lock(&mutx);
			printf("after : %s\n", select_query(&sql, "aa"));
			pthread_mutex_unlock(&mutx);

			//printf("after : %s\n", select_query(&sql, "aa"));

			if (strcmp(msg, "sdf") == 0) {
				write(clnt->sock, "ID Right", 10);
				clnt->state = 1.1;
			}
			else {
				write(clnt->sock, "ID Wrong", 10);
				clnt->state = 1;
			}
		}

		if (clnt->state == 1.1) {
			read(clnt->sock, msg, sizeof(msg));

			if (strcmp(msg, "hot111") == 0) {
				write(clnt->sock, "PW Right", 10);
				clnt->state = 3;
			}
			else {
				write(clnt->sock, "PW Wrong", 10);
				clnt->state = 1.1;
			}
		}

		if (clnt->state == 2) {

		}

	}

}

void* draw_thread(void *arg)
{
	
}

