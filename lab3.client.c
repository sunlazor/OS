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
  S_CONN, S_DISC, S_TIME, COND, EXIT
};

int main()
{
  //char path[] = "~/os/lab2/data";
  char path[] = "data";
  char key_num = 111;
  key_t key;
  int key_id;
  // char status = 1;
  client.status = IDLE;
  //char text[] = "YO BRO, YOUR SERVER SUX";

  // buff.type = 1;
  //memcpy(buff.text, text, sizeof(text));
  // strcpy(client.text, "YO BRO, YOUR SERVER SUX");
  // printf("text:%s\n", buff.text);

  key = ftok(path, key_num);
  key_id = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);
  // printf("key_id:%d\n", key_id);

  // printf("msgsnd status:%d\n", msgsnd(key_id, &buff, sizeof(buff.text), 0));
  // printf("errno #%d: %s\n", errno, strerror(errno));

  //printf("msgctl status:%d\n", msgctl(key_id, IPC_RMID, NULL));

  while(client.status != EXIT)
  {
    switch(client.status)
    {
      case IDLE:
      {
        printf("Insert command\n8: Client exit\n1: Connect server\n");
        scanf("%d", &client.status);
        // printf("Client status: %d\n", client.status);
      } break;
      case C_CONN:
      {
        printf("C_CONN\n");
        int r_msgsnd = msgsnd(key_id, &client, 0, IPC_NOWAIT);
        // printf("msgsnd status: %d\n", r_msgsnd);
        // printf("errno #%d: %s\n", errno, strerror(errno));
        if(r_msgsnd == -1)
        {
          printf("msgsnd status: %d\n", r_msgsnd);
          printf("errno #%d: %s\n", errno, strerror(errno));
          client.status = EXIT;
          break;
        } 
        else
        {
          printf("msgsnd OK\n");
          int r_msgrcv = msgrcv(key_id, &client, 0, S_CONN, 0);
          if(r_msgrcv == -1)
          {
            printf("msgrcv status: %d\n", r_msgrcv);
            printf("errno #%d: %s\n", errno, strerror(errno));
            client.status = EXIT;
            break;
          }
          else printf("msgrcv OK\n");          
        }
        printf("Connected!\n");
        printf("Insert command\n2: Disconnect server\n3: Ask message\n");
        scanf("%d", &client.status);        
      } break;
      case COND:
      {
        printf("Insert command\n2: Disconnect server\n3: Ask message\n");
        scanf("%d", &client.status);
      } break;
      case C_DISC:
      {
        int r_msgsnd = msgsnd(key_id, &client, 0, IPC_NOWAIT);
        if(r_msgsnd == -1)
        {
          printf("msgsnd status: %d\n", r_msgsnd);
          printf("errno #%d: %s\n", errno, strerror(errno));
          client.status = EXIT;
          break;
        } 
        else
        {
          printf("msgsnd OK\n");
          int r_msgrcv = msgrcv(key_id, &client, 0, S_DISC, 0);
          if(r_msgrcv == -1)
          {
            printf("msgrcv status: %d\n", r_msgrcv);
            printf("errno #%d: %s\n", errno, strerror(errno));
            client.status = EXIT;
            break;
          }
          else printf("msgrcv OK\n");        
        }
        printf("Disonnected!\n");
        client.status = IDLE;
      } break;
      case C_TIME:
      {
        int r_msgsnd = msgsnd(key_id, &client, 0, IPC_NOWAIT);
        if(r_msgsnd == -1)
        {
          printf("msgsnd status: %d\n", r_msgsnd);
          printf("errno #%d: %s\n", errno, strerror(errno));
          client.status = EXIT;
          break;
        } 
        else
        {
          printf("msgsnd OK\n");
          int r_msgrcv = msgrcv(key_id, &client, sizeof(client.text), S_TIME, 0);
          if(r_msgrcv == -1)
          {
            printf("msgrcv status: %d\n", r_msgrcv);
            printf("errno #%d: %s\n", errno, strerror(errno));
            client.status = EXIT;
            break;
          }
          else printf("msgrcv OK\n");        
        }
        printf("Message: %s\n", client.text);
        client.status = COND;
      } break;
      default: 
      {
        printf("Unknown command!");
        client.status = C_DISC;
        msgsnd(key_id, &client, 0, IPC_NOWAIT);
        msgrcv(key_id, &client, 0, S_DISC, 0);
        client.status = EXIT;
      }
    }
    sleep(1);
    printf("Next iteration\n");
  }

  printf("Client exit\n");
  return 0;
}
