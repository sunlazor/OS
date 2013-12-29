#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

struct client {
  long status;
  char text[555];
} client;

enum statuses
{
  IDLE, C_CONN, C_DISC, C_TIME, 
  S_CONN, S_DISC, S_TIME
};

int main()
{
  //char path[] = "~/os/lab2/data";
  char path[] = "data";
  char key_num = 111;
  key_t key;
  int key_id;
  int server_time_left = 60;
  client.status = IDLE;
  //ssize_t b_recieved;

  key = ftok(path, key_num);
  key_id = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);
  //printf("key_id:%d\n", key_id);
  //printf("sizeof:%d\n", sizeof(buff.text));

  while(server_time_left-- > 0)
  {
    switch (client.status)
    {
      case IDLE:
        if(msgrcv(key_id, &client, 0, C_CONN, IPC_NOWAIT) > -1)
        {
          client.status = S_CONN;
          msgsnd(key_id, &client, 0, 0);
        }
        break;
      case S_CONN:
        if(msgrcv(key_id, &client, 0, C_TIME, IPC_NOWAIT) > -1)
        {
          client.status = S_TIME;
          strcpy(client.text, "YO BRO!");
          msgsnd(key_id, &client, sizeof(client.text[555]), 0);
          client.status = S_CONN;
        }
        if(msgrcv(key_id, &client, 0, C_DISC, IPC_NOWAIT) > -1)
        {
          client.status = S_DISC;
          msgsnd(key_id, &client, 0, 0);
          client.status = IDLE;
        }
        break;
    }
    // b_recieved = msgrcv(key_id, &buff, sizeof(buff.text), CONN, IPC_NOWAIT);
    // printf("msgrcv status: %d\n", b_recieved);
    // printf("errno #%d: %s\n", errno, strerror(errno));
    // if(b_recieved > 0)
    // {
    //   printf("Recieved!\n");
    //   printf("Message: %s\n", buff.text);
    //   break;
    // }
    printf("Client status: %d\n", client.status);
    printf("Server time left: %d\n", server_time_left);
    sleep(1);
  }

  // if(b_recieved < 0) printf("No Message :(\n");
  msgctl(key_id, IPC_RMID, NULL);
  return 0;
}
