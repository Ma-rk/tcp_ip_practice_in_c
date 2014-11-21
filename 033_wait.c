#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
  int status;
  pid_t pid = fork();

  if(pid == 0)
    return 3;
  else {
    printf("Child 1 PID: %d \n", pid);
    pid = fork();
    if(pid == 0){
      exit(7);
    }else{
      printf("Child 2 PID: %d \n", pid);
      wait(&status);
      printf("value of status: %d\n", status);
      if(WIFEXITED(status))
        printf("Child send one: %d \n", WEXITSTATUS(status));

      wait(&status);
      printf("value of status: %d\n", status);
      if(WIFEXITED(status))
        printf("Child send two: %d \n", WEXITSTATUS(status));

      sleep(30);
    }
  }
  return 0;
}
