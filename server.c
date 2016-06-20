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
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ncurses.h>
#include <pthread.h>

#include "serversocket.h"

void* clnt_connection(void *arg);
void* draw_menu(void *arg);

int main(int argc, char **argv)
{
	int ret;
	Client *clnt = (Client*)malloc(sizeof(Client));
	pthread_t connect_thread, draw_thread;
	
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	init_serv_sock(argv[1]);
	
	printf("Waiting...\n");

	while(1) {
		clnt = connect_client();

		if (clnt->sock == -1) {
			continue;
		}

		//printf("sock : %d\t, addr : %s\n", clnt->sock, inet_ntoa(clnt->sock_addr.sin_addr));

		pthread_create(&connect_thread, NULL, clnt_connection, (void*) clnt);
		//pthread_create(&draw_thread, NULL, draw_thread, (void*)NULL);

	}

	return 0;
}

void* clnt_connection(void *arg)
{
	Client *clnt = (Client*) arg;
}

void* draw_thread(void *arg)
{
	
}

