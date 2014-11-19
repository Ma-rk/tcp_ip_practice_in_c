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
  int sd;
  FILE *fp;

  char buf[BUF_SIZE];
  int read_cnt;
  struct sockaddr_in serv_addr;
  if (argc != 3){
  	printf("Usage: %s, <IP> <port>", argv[0]);
  	exit(1);
  }

  fp = fopen("got.dat", "wb");
  sd = socket(PF_INET, SOCK_STREAM, 0);

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if((connect(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) == -1)
  	errh("connect() err");


  while((read_cnt = read(sd, buf, BUF_SIZE)) != 0){
  	printf("recieved seg: %s\n", buf);
  	fwrite((void*)buf, 1, read_cnt, fp);
  }

  puts("Received file data");
  write(sd, "Thanks.", 10);

  fclose(fp);
  close(sd);

  return 0;
}