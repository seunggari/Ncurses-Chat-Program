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
	char login_id[10];
	char join_id[10], join_pw[10];
	char msg[BUFSIZE];
	Client *clnt = (Client*) arg;
	MYSQL sql;

	init_sql(&sql);

	printf("Connect!!\tIP : %s\n", inet_ntoa(clnt->sock_addr.sin_addr));

	while(1) {

		if (clnt->state == 0) {
			printf("menu\n");
			read(clnt->sock, msg, sizeof(msg));
			clnt->state = atof(msg);
		}

		if (clnt->state == 1) {
			printf("id\n");
			read(clnt->sock, msg, sizeof(msg));
			strcpy(login_id, msg);

			if (strcmp(select_id_query(&sql, msg), "right") == 0) {
				write(clnt->sock, "ID Right", 10);
				clnt->state = 1.1;
			}

			else {
				write(clnt->sock, "ID Wrong", 10);
				clnt->state = 1;
			}
		}

		if (clnt->state == 1.1) {
			printf("pw\n");
			read(clnt->sock, msg, sizeof(msg));

			if (strcmp(select_pw_query(&sql, login_id, msg), "right") == 0) {
				write(clnt->sock, "PW Right", 10);
				clnt->state = 3;
			}

			else {
				write(clnt->sock, "PW Wrong", 10);
				clnt->state = 1.1;
			}
		}

		if (clnt->state == 2) {
			printf("join\n");
			read(clnt->sock, msg, sizeof(msg));
			strcpy(join_id, msg);

			read(clnt->sock, msg, sizeof(msg));
			strcpy(join_pw, msg);

			if (strcmp(insert_query(&sql, join_id, join_pw), "right") == 0) {
				write(clnt->sock, "Success", 10);
				clnt->state = 0;
			}

			else if (strcmp(insert_query(&sql, join_id, join_pw), "false") == 0){
				write(clnt->sock, "Fail", 10);
				clnt->state = 2;
			}
		}
	}
	/* while */
}

void* draw_thread(void *arg)
{
	
}

