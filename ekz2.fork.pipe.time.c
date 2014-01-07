// Экзамен. Задача 2.
// Передать текущую дату между родительским и дочерним процессом через pipe.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main (void)
{
    time_t t_time = time(NULL);
    char readbuffer[64];
    int fd[2];
    pipe(fd);

    int id;
    id = fork();

    if(id == 0)
    {
        printf("+Start child work\n");
        close(fd[1]);
        read(fd[0], readbuffer, sizeof(readbuffer));
        printf("Received time: %s", readbuffer);
        printf("+Finish child work\n");
        return 0;
    }
    else
    {
        printf("+Start parent work\n");
    	char * time_text = asctime(localtime(&t_time));
        close(fd[0]);
        write(fd[1], time_text, (strlen(time_text) + 1));
        printf("+Finish parent work\n");
        return 0;
    }
    return 0;
}
