// ОС. Лаб. 1.2
// Общение родительского и дочернего процесса.
// Родительский пишет дочернему.

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (void)
{
    int fd[2];
    int id;
    char string[] = "Jaaasooon!\n";
    char readbuffer[64];
    pipe(fd);
    id = fork();

    if(id == 0)
    {
        printf("+Start child work\n");
        close(fd[1]);
        read(fd[0], readbuffer, sizeof(readbuffer));
        printf("Received string: %s", readbuffer);
        printf("+Finish child work\n");
        return 0;
    }
    else
    {
        printf("+Start parent work\n");
        printf("Parent ID %d\n", id);
        close(fd[0]);
        write(fd[1], string, (strlen(string) + 1));
        printf("+Finish parent work\n");
        return 0;
    }
    return 0;
}
