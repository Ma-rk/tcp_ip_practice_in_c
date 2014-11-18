#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void errh(char *message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int argc, char *argv[]){
  int sock;
  char msg[BUF_SIZE];
  struct sockaddr_in my_addr, your_addr;
  socklen_t addr_size;
  int str_len, i;

  if(argc != 2){
    printf("Usage: %s <port> \n", argv[0]);
    exit(1);
  }

  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if(sock == -1)
  	errh("socket() err!!");

  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  my_addr.sin_port = htons(atoi(argv[1]));

  if(bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1)
  	errh("bind() err!!");

  printf("recieving...\n");
  for(i=0; i<3; i++){
    sleep(5);
    addr_size = sizeof(your_addr);
    str_len = recvfrom(sock, msg, BUF_SIZE, 0, (struct sockaddr*)&your_addr, &addr_size);
    printf("Msg %d: %s\n", i+1, msg);
  }
  printf("recieved.\n");
  close(sock);
  
  return 0;
}