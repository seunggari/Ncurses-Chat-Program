/*
 * =====================================================================================
 *
 *       Filename:  serversocket.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 06월 17일 15시 10분 08초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Seunghoon, Choi
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include <netinet/in.h>

typedef struct _Client
{
	int sock;
	struct sockaddr_in sock_addr;
	double state;
}Client;
//extern Client *clnt;

void init_serv_sock(char *serv_port);
Client* connect_client();
void error_handling(char *error_msg);

#endif
