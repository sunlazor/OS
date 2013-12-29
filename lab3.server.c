#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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
  int i = 5;
  ssize_t b_recieved;

  key = ftok(path, key_num);
  key_id = msgget(key, IPC_CREAT | 0002 | 0004 | 0200 | 0400);
  printf("key_id:%d\n", key_id);
  printf("sizeof:%d\n", sizeof(buff.text));

  while(i-- > 0)
  {
    b_recieved = msgrcv(key_id, (void *)&buff, sizeof(buff.text), 0, IPC_NOWAIT);
    printf("msgrcv status: %d\n", b_recieved);
    printf("errno #%d: %s\n", errno, strerror(errno));
    if(b_recieved > 0)
    {
      printf("Recieved!\n");
      printf("Message: %s\n", buff.text);
      break;
    }
    sleep(1);
  }

  if(b_recieved < 0) printf("No Message :(\n");
  msgctl(key_id, IPC_RMID, NULL);
  return 0;
}
