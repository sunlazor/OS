// Экзамен. Задача 5.
// Передать текущую дату между родительским и 
// дочерним процессом через файл.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

int main()
{
	FILE * a_file;
	time_t a_time = time(NULL);
	char * time_text = ctime(&a_time);
	int time_len = strlen(time_text) * sizeof(char);
	// printf("time_len: %d\n", time_len);

	int id = fork();
	if (id != 0)
	{
		char * time_text = (char *)malloc(time_len);
		wait(NULL);
		a_file = fopen("data", "r");
		int r_fread = fread(time_text, time_len, 1, a_file);
		// printf("r_fread: %d\n", r_fread);
		printf("time_text: %s\n", time_text);
		close(a_file);
		remove("data");
		free(time_text);
		return 0;
	}
	else
	{
		a_file = fopen("data", "w");
		time_t a_time = time(NULL);
		char * time_text = ctime(&a_time);
		fwrite(time_text, time_len, 1, a_file);
		close(a_file);
		return 0;
	}
}
