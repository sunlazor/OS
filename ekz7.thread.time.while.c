// Экзамен. Задача 7.
// Cоздать 10 потоков. Каждый поток выводит на экран
// thid и текущее время в бесконечном цикле. Главный 
// поток ждет 60 секунд и принудительно завершает все потоки.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void * thread_func(void *arg)
{
	while(1)
	{
		time_t t_time = time(NULL);    
		char * time_text = ctime(&t_time);
		printf("Thread: %x  Data and Time: %s", pthread_self(), time_text);  
	}	   
}

int main(int argc, char **argv)
{
    int i;
    pthread_t thread;  
    for(i = 0; i < 10; i++)
    {
        pthread_create(&thread, NULL, thread_func, NULL);
    }
    sleep(30);
	exit(0);
    return 0;    
}
