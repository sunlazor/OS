// Экзамен. Задача 9.
// Создать поток. С помощью semaphore блокировать доступ 
// к глобальной переменной. Обязательно показать динамику.

#include <stdio.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>

int resourse = 0xF1F0;
sem_t semap;

void * work(void *arg)
{
    // int sem_init(sem_t *sem, int pshared, unsigned int value);
    int timer_th, r_semap;
    for (timer_th = 0; timer_th < 9; ++timer_th)
    {
        printf("CHILD THREAD: Trying take main resourse...\n");
        r_semap = sem_trywait(&semap);
        if (r_semap == 0)
        {
            printf("CHILD THREAD: Success! Main resourse: %d\n", resourse);
            sem_post(&semap);
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
    int r_sem_init = sem_init(&semap, 0, 1);
    printf("r_sem_init status: %d\n", r_sem_init); 
    if (r_sem_init != 0)
    {
        printf("errno #%d: %s\n", errno, strerror(errno));
        return 0;
    }

    pthread_t thread;
    pthread_create(&thread, NULL, work, NULL);

    int timer;
    for (timer = 0; timer < 10; ++timer)
    {
        if (timer == 0)
        {
            printf("MAIN THREAD: Main resourse free.\n");
        }
        if (timer == 2)
        {
            sem_wait(&semap);
            printf("MAIN THREAD: Main resourse blocked.\n");
        }
        if (timer == 6)
        {
            sem_post(&semap);
            printf("MAIN THREAD: Main resourse free.\n");
        }
        sleep(1);
    }

    sem_destroy(&semap);

    return 0;
}

// Динамика плохая. Поциент мертв. Помянем
