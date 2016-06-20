/*
 * =====================================================================================
 *
 *       Filename:  serversocket.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 06월 17일 15시 12분 22초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Seunghoon, Choi
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>		//exit
#include <netinet/in.h>	//struct addr_in
#include <string.h>		//memset

#include "serversocket.h"

#define SERVERIP "127.0.0.1"

static int serv_sock, clnt_sock;

void init_serv_sock(char *serv_port)
{
	struct sockaddr_in serv_addr;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	if (serv_sock == -1) {
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(serv_port));

	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("bind() error");
	}

	if (listen(serv_sock, 5) == -1) {
		error_handling("listen() error");
	}
}

Client* connect_client()
{
	int clnt_addr_size;
	struct sockaddr_in clnt_addr;

	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

	Client *clnt = (Client*)malloc(sizeof(Client));
	clnt->sock = clnt_sock;
	clnt->sock_addr = clnt_addr;

	//printf("sock : %d, addr: %s\n", clnt->sock, inet_ntoa(clnt_addr.sin_addr));

	return clnt;
}

void error_handling(char *error_msg)
{
	perror(error_msg);
	exit(1);
}


