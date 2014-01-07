// Экзамен. Задача 3.
// Передать текущую дату между родительским и дочерним процессом через fifo.

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

//int mkfifo(char* path, int mode, int dev);

int  main(int argc, char* *argv)
{
	int fd = 0, result = 0, size = 0;
	char resstring[64];
	char name[] = "data.fifo";
	time_t t_time = time(NULL);
	int date_len = strlen(asctime(localtime(&t_time)));

	memset(resstring, 0, sizeof(resstring));
	//memcpy(name, "10", 2);

	if (mkfifo(name, 0666) < 0)
	{
		printf("mkfifo error. errno#%d: %s\n", errno, strerror(errno));
		return -1;
	}

	int id = fork();
	if (id == 0)
	{
        printf("+Start child work\n");
		if ((fd = open(name, O_RDONLY)) < 0) {
			printf("fifo open error. errno#%d: %s\n", errno, strerror(errno));
			return -1;
		}
		size = read(fd, resstring, sizeof(resstring));
		if (size != date_len)
		{
			printf("child fifo read error. errno#%d: %s\n", errno, strerror(errno));
			close(fd);
			return -1;
		}
		printf("Recieved text: %s", resstring);
		close(fd);
		remove(name);
        printf("+Finish child work\n");
	}
	else
	{
        printf("+Start parent work\n");
		if ((fd = open(name, O_WRONLY)) < 0)
		{
			printf("parent fifo open error. errno#%d: %s\n", errno, strerror(errno));
			return -1;
		}
		t_time = time(NULL);
    	char * time_text = asctime(localtime(&t_time));
		size = write(fd, time_text, strlen(time_text));
		if (size != date_len)
		{
			printf("parent fifo write error. errno#%d: %s\n", errno, strerror(errno));
			close(fd);
			return -1;
		}
		close(fd);
        printf("+Finish parent work\n");
	}
	return 0;
}
