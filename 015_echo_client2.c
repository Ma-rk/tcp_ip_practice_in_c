#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void errh(char*message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int argc, char *argv[]){
  int sock;
  char message1[BUF_SIZE];
  char message2[BUF_SIZE];
  int str_len, recv_len, recv_cnt;
  struct sockaddr_in serv_addr;

  if(argc != 3){
    printf("not enugh arguments");
    exit(1);
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock == -1)
    errh("socket() err!!");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    errh("connect() err!!");
  else
    puts("Connected...........");

  while(1){
    fputs("Input message(Q to quit): ", stdout);
    fgets(message1, BUF_SIZE, stdin);

    if(!strcmp(message1, "q\n") || !strcmp(message1, "Q\n"))
      break;

    str_len =  write(sock, message1, strlen(message1));

    recv_len = 0;
    printf("str_len: %d\n", str_len);
    while(recv_len < str_len){
      printf("1...\n");
      recv_cnt = read(sock, &message2[recv_len], BUF_SIZE-1);
      printf("2... %d\n", recv_cnt);
      if(recv_cnt == -1)
        errh("read() err!!");
      recv_len += recv_cnt;
      printf("3...\n");
    }
    printf("after of while\n");
    message2[str_len] = 0;
    printf("Msg from server: %s\n", message2);
  }
  close(sock);

  return 0;
}
