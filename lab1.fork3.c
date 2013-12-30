// ОС. Лаб. 1.1
// Общение родительского и дочернего процесса.
// Родительский пишет дочернему, но без закрытия других пайпов.

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (void)
{
    int fd[2];
    int id;
    char string[] = "Mario fix this pipe!\n";
    char readbuffer[64];
    pipe(fd);
    id = fork();

    if(id == 0)
    {
        printf("ID child %d\n", id);
        // close(fd[1]);
        read(fd[0], readbuffer, sizeof(readbuffer));
        printf("Received string: %s", readbuffer);
        return 0;
    }
    else
    {
        printf("ID parrent %d\n", id);
        // close(fd[0]);
        // write(fd[1], string, (strlen(string) + 1));
        return 0;
    }
    return 0;
}
