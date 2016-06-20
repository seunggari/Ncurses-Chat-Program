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
#define MAX 50

int main(int argc, char **argv)
{
	int clnt_sock;
	char msg[MAX];

	WINDOW *help, *chat, *list, *input;

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	init_clnt_sock(argv[1]);

	initscr();
	//init_pair(1, COLOR_WHITE, COLOR_BLUE);
	//bkgd(1);

	//login_menu();

	help = newwin(LINES, COLS/6, 1);
	box(help, 0, 0);
	scrollok(win_out, TRUE);
	wrefresh(win_out);

	win_in = newwin(5, COLS, LINES-10, 0);
	box(win_in, 0, 0);
	wrefresh(win_in);

	while(1) {
		mvwgetstr(win_in, 1, 1, msg);
		wprintw(win_out, "msg : %s\n", msg);
		wrefresh(win_out);
		wrefresh(win_in);
	}

	endwin();

	return 0;
}

void login_menu()
{
	char input_id[MAX] = "", input_pw[MAX] = "";

	while(1) {
		mvprintw(10, 10, "Enter your ID : %s\n", input_id);
		mvprintw(15, 10, "Enter your PW : %s\n", input_pw);
		refresh();
		mvgetstr(10, 26, input_id);

		if (strcmp(input_id, "seung") == 0) {
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
		mvprintw(10, 10, "Enter your ID : %s\n", input_id);
		mvprintw(15, 10, "Enter your PW : %s\n", input_pw);
		refresh();
		mvgetstr(15, 26, input_pw);

		if (strcmp(input_pw, "hot111") == 0) {
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
