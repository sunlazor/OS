// Экзамен. Задача 10.
// Создать поток. Поток преобразует переданный адрес памяти 
// в int * и записывает в него в цикле 10 элементов (int* + i). 
// После каждой итерации засыпает на 2 секунду. 
// Главный поток вывыподт на экран весь массив каждую секунду.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * work(void *arg)
{
    int j;
    for (j = 0; j < 10; ++j)
    {
        sleep(2);
        *((int *)arg + j) = j + 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int * memory = (int *)malloc(10 * sizeof(int));
    pthread_t thread;
    pthread_create(&thread, NULL, work, memory);
    sleep(1);
    int p, i;
    for (i = 0; i < 22; ++i)
    {
        printf("==Array==\n");
        for ( p = 0; p < 10; ++p)
        {
            printf("%2d", *(memory + p));
            if (p != 9)
                printf(" ");
            else 
                printf("\n");
        }
        sleep(1);
    }
    exit(0);
    free(memory);
    return 0;    
}
