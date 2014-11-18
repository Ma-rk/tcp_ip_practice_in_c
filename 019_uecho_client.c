#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void errh(char *msg){
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int argc, char *argv[]){
  int sock;
  char msg[BUF_SIZE];
  int str_len;
  socklen_t addr_size;

  struct sockaddr_in serv_addr, clnt_addr;

  if(argc != 3){
    printf("Usage: %s ,<ip> <port> \n", argv[0]);
    exit(1);
  }

  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if(sock == -1)
    errh("UDP socket creation err!!");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  while(1){
    fputs("Insert msg(Q too quit): ", stdout);
    fgets(msg, sizeof(msg), stdin);
    if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
      break;

                sendto(sock, msg, strlen(msg),  0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    str_len = recvfrom(sock, msg, BUF_SIZE,     0, (struct sockaddr*)&clnt_addr, &addr_size);
    msg[str_len] = 0;
    printf("Msg from server: %s\n", msg);
  }
  close(sock);
  return  0;
}
