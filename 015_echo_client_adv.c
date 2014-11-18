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
  int str_len;
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

    write(sock, message1, strlen(message1));
    str_len = read(sock, message2, BUF_SIZE-1);
    message2[str_len] = 0;
    printf("Msg from server: %s\n", message2);
  }
  close(sock);

  return 0;
}
