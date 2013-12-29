#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

struct msgbuf {
  long type;
  char text[555];
} buff;

int main()
{
  //char path[] = "~/os/lab2/data";
  char path[] = "data";
  char key_num = 111;
  key_t key;
  int key_id;
  struct msgbuf buff;
  //char text[] = "YO BRO, YOUR SERVER SUX";

  buff.type = 1;
  //memcpy(buff.text, text, sizeof(text));
  strcpy(buff.text, "YO BRO, YOUR SERVER SUX");
  printf("text:%s\n", buff.text);

  key = ftok(path, key_num);
  key_id = msgget(key, IPC_CREAT | 0002 | 0004 | 0200 | 0400);
  printf("key_id:%d\n", key_id);

  printf("msgsnd status:%d\n", msgsnd(key_id, (void *)&buff, sizeof(buff.text), 0));
  printf("errno #%d: %s\n", errno, strerror(errno));

  //printf("msgctl status:%d\n", msgctl(key_id, IPC_RMID, NULL));

  printf("Sent!\n");
  return 0;
}
