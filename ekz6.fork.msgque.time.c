// Экзамен. Задача 6.
// Передать текущую дату между родительским и 
// дочерним процессом через очередь сообщений.

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <time.h>
#include <errno.h>

struct message
{
	long type;
	char date_text[64];
};

int main()
{
	int key_id;

	int id = fork();
	if (id != 0)
	{
		printf("+Start parent work\n");
		key_t key = ftok("data", 0xF1F0);
		key_id = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);
		// printf("parent msgget status: %d\n", key_id);
		// printf("errno #%d: %s\n", errno, strerror(errno));

		struct message date_now;
		time_t a_time = time(NULL);
		char * text = asctime(localtime(&a_time));
		// printf("text: %s\n", text);
		strcpy(date_now.date_text, text);
		// printf("date_now.date_text: %s\n", date_now.date_text);
		date_now.type = 1;

		// printf("+to msgsnd\n");
		int r_msgsnd = msgsnd(key_id, &date_now, sizeof(date_now.date_text), IPC_NOWAIT);
		// printf("msgsnd status: %d\n", r_msgsnd);
		// printf("errno #%d: %s\n", errno, strerror(errno));
		wait(NULL);
        printf("+Finish parent work\n");

        return 0;
	}
	else
	{
        printf("+Start child work\n");
		key_t key = ftok("data", 0xF1F0);
        key_id = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);
		// printf("child msgget status: %d\n", key_id);
		// printf("errno #%d: %s\n", errno, strerror(errno));

		struct message date_now;
        int r_msgrcv = msgrcv(key_id, &date_now, sizeof(date_now.date_text), 1, 0);
		// printf("msgrcv status: %d\n", r_msgrcv);
		// printf("errno #%d: %s\n", errno, strerror(errno));

		printf("Time is: %s\n", date_now.date_text);

        printf("+Finish child work\n");

		return 0;
	}
}
