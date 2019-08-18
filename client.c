#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <signal.h>

#include "client.h"

#define NICK_LEN 15

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) & size);
	resizeterm(size.ws_row, size.ws_col);
}

int chat(){
	WINDOW* menu;
	WINDOW* submenu;
	WINDOW* chat;
	WINDOW* subchat;
	WINDOW* users;
	WINDOW* subusers;

	int check = 0;
	int s_button = 0;
	int row =0, col =0;
	int exit_fl = 0;
	initscr();
	signal(SIGWINCH, sig_winch);
	cbreak();
	noecho();
	curs_set(TRUE);
	refresh();
	start_color();
	draw_menu(&menu, &submenu);
	draw_users(&users, &subusers);
	draw_chat(&chat, &subchat);
	keypad(chat, TRUE);
	while(s_button != KEY_F(3)){
		s_button = wgetch(chat);
		getyx(subchat, row, col);
		switch( s_button){
			case KEY_F(1):
					
					break;
			case KEY_F(2):
					
					break;
			case KEY_F(3):
					break;
			default:
					waddch(subchat, s_button);
					break;
		}
		wrefresh(subchat);
	}
	delwin(menu);
	delwin(chat);
	delwin(users);
	delwin(submenu);
	delwin(subchat);
	delwin(subusers);
	refresh();
	endwin();
	return 0;
}
int draw_menu(WINDOW** menu, WINDOW** submenu){
	*menu = newwin(5, 100, 1, 1);
	if (*menu == NULL){
		printf("\nDRAW_MENU WIN ERROR\n");
		return -1;
	}
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	box(*menu, 0, 0);
	*submenu = derwin(*menu, 3, 98, 1, 1);
	wbkgd(*menu, COLOR_PAIR(1));
	wbkgd(*submenu, COLOR_PAIR(2));
	wmove(*submenu, 0, 0);
	wprintw(*submenu, "\n F1 - log in, F2 - log out, F3 - exit");
	wrefresh(*submenu);
	wrefresh(*menu);
	return 0;
}

int draw_chat(WINDOW** chat, WINDOW** subchat){
	char fnick[NICK_LEN] = {" "};
	*chat = newwin(40, 100, 6 , 1);
	if (*chat == NULL){
		printf("\nCHAT NEWWIN ERROR\n");
		return -1;
	}
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	box(*chat, 0, 0);
	*subchat = derwin(*chat, 38, 98, 1, 1);
	wbkgd(*chat, COLOR_PAIR(1));
	wbkgd(*subchat, COLOR_PAIR(2));
	wrefresh(*chat);
	wrefresh(*subchat);
	wmove(*subchat, 0, 0);
//	wprintw(*subchat, "Enter your nickname\n");
//	curs_set(TRUE);
//	wgetnstr(*subchat, fnick, NICK_LEN);
//	wclear(*subchat);
//	wmove(*subchat, 0, 0);
//	wrefresh(*subchat);
	return 0;
}

int draw_users(WINDOW** users, WINDOW** subusers){
	*users = newwin(45, 20, 1, 102);
	if(*users == NULL){
		printf("\nUSERS NEWWIN ERROR\n");
		return -1;
	}
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	box(*users, 0, 0);
	*subusers = derwin(*users, 43, 18, 1, 1);
	wbkgd(*users, COLOR_PAIR(1));
	wbkgd(*subusers, COLOR_PAIR(2));
	wrefresh(*users);
	wrefresh(*subusers);
	return 0;
}

int main(){
	chat();
	return 0;
}
