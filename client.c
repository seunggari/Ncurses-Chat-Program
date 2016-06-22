/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 06월 17일 16시 11분 10초
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
#include <ncurses.h>

#include "clientsocket.h"
#define BUFSIZE 500
#define MAX 50

void select_menu(int sock);
void login_menu(int sock);
void member_menu(int sock);
void after_login(int sock);

int main(int argc, char **argv)
{
	int sock;
	
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	sock = init_clnt_sock(argv[1]);

	initscr();

	while(1) {
		select_menu(sock);
	}

	//after_login(sock);

	endwin();

	return 0;
}

void select_menu(int sock)
{
	char choice[10];

	while(1) {
		clear();
		mvprintw(LINES/3,	COLS/3, "Welcome to Chat Program\n");
		mvprintw(LINES/3+2, COLS/3, "Join First, Before Login\n"); 
		mvprintw(LINES/3+4, COLS/3, "Please Select the Menu\n");
		mvprintw(LINES/3+6, COLS/3, "1. Login\t2. Join\n");
		refresh();

		mvgetstr(LINES/3+8, COLS/3, choice);

		if (strcmp(choice, "1") == 0) {
			write(sock, choice, sizeof(choice));
			clear();
			login_menu(sock);
			break;
		}
		
		else if (strcmp(choice, "2") == 0) {
			write(sock, choice, sizeof(choice));
			clear();
			member_menu(sock);
			break;
		}
		
		else {
			continue;
		}
	}
}

void login_menu(int sock)
{
	char input_id[MAX] = "", input_pw[MAX] = "";
	char msg[MAX];
	memset(msg, 0, MAX);

	while(1) {
		mvprintw(8,  10, "Login!\n");
		mvprintw(10, 10, "Enter your ID : %s\n", input_id);
		mvprintw(15, 10, "Enter your PW : %s\n", input_pw);
		refresh();
		mvgetstr(10, 26, input_id);

		write(sock, input_id, sizeof(input_id));
		read(sock, msg, sizeof(msg));

		if (strcmp(msg, "ID Right") == 0) {
			mvprintw(11, 10, "ID Right\n");
			break;
		}

		else {
			mvprintw(11, 10, "ID Wrong\n");
			strcpy(input_id, "");
			continue;
		}
	}

	while(1) {
		mvprintw(8,  10, "Login!\n");
		mvprintw(10, 10, "Enter your ID : %s\n", input_id);
		mvprintw(15, 10, "Enter your PW : %s\n", input_pw);
		refresh();
		mvgetstr(15, 26, input_pw);

		write(sock, input_pw, sizeof(input_pw));
		read(sock, msg, sizeof(msg));

		if (strcmp(msg, "PW Right") == 0) {
			mvprintw(16, 10, "PW Right\n");
			break;
		}

		else {
			mvprintw(16, 10, "PW Wrong\n");
			strcpy(input_pw, "");
			continue;
		}
	}
}

void member_menu(int sock)
{
	char input_id[MAX] = "", input_pw[MAX] = "";	
	char msg[MAX];
	memset(msg, 0, MAX);

	while(1) {
		mvprintw(8,  10, "Join!\n");
		mvprintw(10, 10, "Enter your ID : \n");
		mvprintw(15, 10, "Enter your PW : \n");
		refresh();

		mvgetstr(10, 26, input_id);
		write(sock, input_id, sizeof(input_id));

		mvgetstr(15, 26, input_pw);
		write(sock, input_pw, sizeof(input_pw));

		read(sock, msg, sizeof(msg));

		if (strcmp(msg, "Fail") == 0 ) {
			mvprintw(11, 10, "Invaild Input\n");
			continue;
		}

		break;
	}
}

void after_login(int sock)
{
	char msg[MAX];
	WINDOW *help, *chat, *list, *input;

	help = newwin(LINES/6, COLS, 0, 0);
	mvwprintw(help, 1, 1, "help is /h\n");
	wrefresh(help);

	chat = newwin(LINES/3*2, COLS/3*2, LINES/6, 0);
	scrollok(chat, TRUE);
	wrefresh(chat);

	list = newwin(LINES/3*2, COLS/3*2, LINES/6, COLS/3*2);
	wrefresh(list);

	input = newwin(LINES/6, COLS, LINES/6*5, 0);
	wrefresh(input);

	while(1) {
		mvwgetstr(input, 1, 1, msg);
		wprintw(chat, "msg : %s\n", msg);
		wrefresh(input);
		wrefresh(chat);
	}

}
