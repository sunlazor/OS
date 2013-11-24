// Лаб. 2.1. FIFO
// 100 процессов общаются друг с другом 
// с помощью разделяемой памяти

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

//int mkfifo(char* path, int mode, int dev);

int  main(int argc, char* *argv)
{
	int fd = 0, result = 0, size = 0;
	char resstring[14];
	char name[] = "20131028.fifo";

	memset(resstring, 0, sizeof(resstring));
	memcpy(name, "10", 2);
	if (mkfifo(name, 0666) < 0)
	{
		// ОШИБКА
	}
	if (fork())
	{
		if ((fd = open(name, O_WRONLY)) < 0){
			// ОШИБКА ОТКРЫТИЯ fifo
			return -1;
		}
		size = write(fd,"20131028", strlen("20131028"));
		if (size!=14)
		{
			// ОШИБКА ПЕРЕДАЧИ СТРОКИ
		}
		close(fd);
	}
	else
	{
		if ((fd=open(name, O_RDONLY)) < 0)
		{
			//
		}
		size = read(fd, resstring, 14);
		if (size!=14)
		{
			//
		}
		printf("Recieved text: %s", resstring);
		close(fd);
	}
	return 0;
}
