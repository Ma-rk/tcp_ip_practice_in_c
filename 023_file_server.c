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
  int serv_sd, clnt_sd;
  FILE * fp;
  char buf[BUF_SIZE];
  char buf2[BUF_SIZE];
  int read_cnt;

  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_size;

  if(argc != 2){
  	printf("Usage: %s <port> \n", argv[0]);
  	exit(1);
  }

  fp = fopen("003_low_open.c", "rb");
  if((serv_sd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    errh("socket() err");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  if(bind(serv_sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
  	errh("bind() err");

  if(listen(serv_sd, 5) == -1)
    errh("listen() err");

  clnt_addr_size = sizeof(clnt_addr);
  if((clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_addr, &clnt_addr_size)) == -1)
    errh("accept() err");

  while(1){
    printf("in while\n");
    //read_cnt = fread((void*)buf, 1, BUF_SIZE, fp);
    read_cnt = fread(buf, 1, BUF_SIZE, fp);
    printf("%d\n", read_cnt);
  	if(read_cnt<BUF_SIZE){
      printf("in if\n");
      write(clnt_sd, buf, read_cnt);
      break;
  	}
  	write(clnt_sd, buf, BUF_SIZE);
  }

  shutdown(clnt_sd, SHUT_WR);
  read(clnt_sd, buf2, BUF_SIZE);
  printf("Msg from client: %s\n", buf2);

  fclose(fp);
  close(clnt_sd);
  close(serv_sd);

  return 0;
}