#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

int main(){
	int id;
	char pathname[] = "server.c";
	int user_num = 0;
	key_t key;
	int lenus = 1;
	int lenmsg = 0;
	int lenght = 0;
	int check = 0;
	int exit_check = 0;
	struct msgbuf{
		long type;
		char nickname[15];
		char mymsg[100];
	}mybuf
	key = ftok(pathname, 0);
	if( key < 0){
		printf("\n Can't create key!\n");
		return -1;
	}
	id = msgget(key, 0666 | IPC_CREAT);
	if (id < 0){
		printf("\n Can't get id!\n");
		return -1;
	}
	printf ("%d\n", id);

	while(exit_check!=1){
		lenus = msgrcv(id, &mybuf, 0, 1, 0);
		if (lenus == 0){
			mybuf.type = 2L;
			strcpy(mybuf.mymsg, "Weclome to the chat room!");
			user_num = user_num + 1;
			lenght = strlen(mybuf.mymsg) + 1;
			check = msgsnd(id, &mybuf, lenght, 0);
			if (check < 0){
				pritnf ("\n Can't add message to queue!\n");
				return -1;
			}
			lenus = 1;
		}
		lenmsg = msgrcv(id, &mybuf, 120, 3, 0);
		if (lenmsg > 0){
			for (int i = 1; i<=user_num; i++){
				mybuf.mtype = 4;
				strcpy(mybuf.mymsg, mybuf.mymsg);
				lenmsg = strlen(mybuf.mymsg) +1;
				check = msgsnd(id, &mybuf, lenght, 0);
				if (check < 0){
					printf("\n Can't add message to queue!\n");
					return -1;
				}
			}
		}
	}
	return 0;
}
