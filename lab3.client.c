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

enum
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
  char stats = IDLE;
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

  while(stats != EXIT)
  {
    printf("stats stats: %d\n", stats);
    switch(stats)
    {
      case IDLE:
      {
        printf("Insert command\n1: Connect server\n8: Exit client\n");
        int r_scanf = scanf("%d", &stats);
        printf("scanf status: %d\n", r_scanf);
        printf("stats stats: %d\n", stats); 
        if((stats < IDLE) || (stats > EXIT))
        {
          printf("Invalid command!\n");
          stats = IDLE;
        }
      } break;
      case C_CONN:
      {
        //printf("C_CONN\n");  
        client.status = C_CONN;
        int r_msgsnd = msgsnd(key_id, &client, 0, IPC_NOWAIT);
        // printf("msgsnd status: %d\n", r_msgsnd);
        // printf("errno #%d: %s\n", errno, strerror(errno));
        if(r_msgsnd == -1)
        {
          printf("msgsnd status: %d\n", r_msgsnd);
          printf("errno #%d: %s\n", errno, strerror(errno));
          stats = EXIT;
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
            stats = EXIT;
            break;
          }
          else 
          {
            printf("msgrcv OK\n");
            stats = COND;
          }
        }  
      } break;
      case COND:
      {
        printf("Stats %d\n", stats);
        printf("Insert command\n2: Disconnect server\n3: Ask message\n");
        int r_scanf = scanf("%d", &stats);
        printf("scanf status: %d\n", r_scanf);
        printf("stats stats: %d\n", stats);   
        if((stats < IDLE) || (stats > EXIT))  
        {
          printf("Invalid command!\n");
          stats = COND;
        }
      } break;
      case C_DISC:
      {
        client.status = C_DISC;
        int r_msgsnd = msgsnd(key_id, &client, 0, IPC_NOWAIT);
        if(r_msgsnd == -1)
        {
          printf("msgsnd status: %d\n", r_msgsnd);
          printf("errno #%d: %s\n", errno, strerror(errno));
          stats = EXIT;
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
            stats = EXIT;
            break;
          }
          else printf("msgrcv OK\n");
        }
        printf("Disonnected!\n");
        stats = IDLE;
      } break;
      case C_TIME:
      {
        client.status = C_TIME;
        int r_msgsnd = msgsnd(key_id, &client, 0, IPC_NOWAIT);
        if(r_msgsnd == -1)
        {
          printf("msgsnd status: %d\n", r_msgsnd);
          printf("errno #%d: %s\n", errno, strerror(errno));
          stats = EXIT;
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
            stats = EXIT;
            break;
          }
          else printf("msgrcv OK\n");
        }
        printf("Message: %s\n", client.text);
        stats = COND;
      } break;
      default:
      {
        printf("Unknown command!\n");
        client.status = C_DISC;
        msgsnd(key_id, &client, 0, IPC_NOWAIT);
        msgrcv(key_id, &client, 0, S_DISC, 0); 
        stats = EXIT;
      }
    }  
    sleep(1);
    printf("Stats status: %d\n", stats);
    //printf("Next iteration\n");
  }
   
  printf("Client exit\n");
  return 0;
}
