// Экзамен. Задача 4.
// Передать текущую дату между родительским и дочерним процессом через разделяемую память.

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>

int main(void)
{
	int key = 0xF1F0;
	key_t key_id = ftok("data", key);

	int shmid;
	char * shm;

	time_t a_time = time(NULL);
	char * time_text = asctime(localtime(&a_time));
	int time_len = strlen(time_text);

    int size = strlen(time_text) * sizeof(char);
    printf("strlen time_text: %d\n", size);
    // printf("timetext: %s\n", time_text);
    // strcpy(time_text, "a");
    // printf("sizeof timetext a: %d\n", size);
    // printf("timetext a: %s\n", time_text);

    int id;
    id = fork();

    if(id != 0)
    {
        printf("+Start parent work\n");

		shmid = shmget(key_id, size, IPC_CREAT | 0666);
	    if(shmid < 0)
	    {
			printf("shmid error. errno#%d: %s\n", errno, strerror(errno));
			return -1;
	    }

		shm = (char*)shmat(shmid, NULL, 0);	
		if(shm == (int*)-1)
	    {
			printf("shmat error. errno#%d: %s\n", errno, strerror(errno));
			return -1;
	    }

		a_time = time(NULL);
		char * time_text = asctime(localtime(&a_time));

		strcpy(shm, time_text);

		wait(NULL);

		shmctl(shmid, IPC_RMID, 0); 
        printf("+Finish parent work\n");
        return 0;
    }
    else
    {
        printf("+Start child work\n");

		shmid = shmget(key_id, size, IPC_CREAT | 0666);
	    if(shmid < 0)
	    {
			printf("shmid error. errno#%d: %s\n", errno, strerror(errno));
			return -1;
	    }

		shm = (char*)shmat(shmid, NULL, 0);	
		if(shm == (int*)-1)
	    {
			printf("shmat error. errno#%d: %s\n", errno, strerror(errno));
			return -1;
	    }
		
        printf("Time is: %s\n", shm);

        printf("+Finish child work\n");
        return 0;
    }
    return 0;



}
