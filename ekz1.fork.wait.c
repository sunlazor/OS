// Экзамен. Задача 1.
// Программа создает дочерний процесс. Родительский 
// процесс ожидает завершения дочернего. Дочерний 
// процесс выводит на экран pid и ppid ждет 10 сек и завершается. 

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (void)
{
    int id;
    id = fork();

    if(id != 0)
    {
        printf("+Start parent work\n");
        wait(NULL);
        printf("+Finish parent work\n");
        return 0;
    }
    else
    {
        printf("+Start child work\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        sleep(3);
        printf("+Finish child work\n");
        return 0;
    }
    return 0;
}
