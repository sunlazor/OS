// Экзамен. Задача 8.
// Создать поток. С помощью Mutex блокировать 
// доступ к глобальной переменной. Обязательно показать динамику.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

int global = 0x31337;

void * work(void *arg)
{
	pthread_mutex_t * m = (pthread_mutex_t *)arg;
    int timer_th;
    for (timer_th = 0; timer_th < 9; ++timer_th)
    {
        printf("CHILD THREAD: Trying take main resourse...\n");
        int r_mutex = pthread_mutex_trylock(m);
        if (r_mutex == 0)
        {
            printf("CHILD THREAD: Success! Main resourse: %d\n", global);
            pthread_mutex_unlock(m);
        }
        else
        {
            printf("CHILD THREAD: Failed! Main resourse busy!\n");
        }
        sleep(1);
    }
    return 0;
}

int main()
{
	// заводим в памяти объект мьютекс
	pthread_mutex_t * m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t *));
	pthread_mutex_init(m, NULL);

	// создаем поток 1
    pthread_t thread;
    pthread_create(&thread, NULL, work, (void *)m);

    int timer;
    for (timer = 0; timer < 10; ++timer)
    {
        if (timer == 0)
        {
            printf("MAIN THREAD: Main resourse free.\n");
        }
        if (timer == 2)
        {
            pthread_mutex_lock(m);
            printf("MAIN THREAD: Main resourse blocked.\n");
        }
        if (timer == 6)
        {
            pthread_mutex_unlock(m);
            printf("MAIN THREAD: Main resourse free.\n");
        }
        sleep(1);
    }

    pthread_mutex_destroy(m);

    return 0;
}
