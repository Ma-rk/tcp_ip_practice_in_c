#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 100

void error_handling(char * message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(void){
  int fd;
  char buf[BUF_SIZE];

  fd = open("data.txt",O_RDONLY);
  if(fd == -1)
    error_handling("open() error!!");
  printf("file descriptor: %d\n", fd);

  if(read(fd, buf, sizeof(buf) == -1))
    error_handling("write() error!!");
  printf("data of file: %s\n", buf);
  close(fd);

  return 0;
}
