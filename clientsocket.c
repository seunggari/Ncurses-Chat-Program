/*
 * =====================================================================================
 *
 *       Filename:  clientsocket.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 06월 17일 16시 51분 47초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Seunghoon, Choi 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>		//memset
#include <sys/socket.h>
#include <netinet/in.h>

#include "clientsocket.h"
#define SERVERIP "127.0.0.1"


void init_clnt_sock(char *clnt_port)
{
	int sock;
	struct sockaddr_in serv_addr;

	sock = socket(PF_INET, SOCK_STREAM, 0);

	if (sock == -1) {
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERVERIP);
	serv_addr.sin_port = htons(atoi(clnt_port));

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("connect() error");
	}
}

void error_handling(char *error_msg)
{
	perror(error_msg);
	exit(1);
}
