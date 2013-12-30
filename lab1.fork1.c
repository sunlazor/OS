// ОС. Лаб. 1.1
// Общение родительского и дочернего процесса.
// Дочерний пишет родительскому.

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (void)
{
    int fd[2];
    int id;
    char string[] = "Hello, Dad!\n";
    char readbuffer[64];
    pipe(fd);
    id = fork();

    if(id == 0)
    {
        printf("+Start child work\n");
        close(fd[0]);
        printf("Len:%d\n", strlen(string));
        write(fd[1], string, (strlen(string) + 1));
        printf("+Finish child work\n");
        return 0;
    }
    else
    {
        printf("+Start parent work\n");
        printf("Parent process ID %d\n", id);
        close(fd[1]);
        read(fd[0], readbuffer, sizeof(readbuffer));
        printf("Received string: %s", readbuffer);
        printf("+Finish parent work\n");
        return 0;
    }
    return 0;
}
