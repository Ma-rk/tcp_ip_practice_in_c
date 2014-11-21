#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[]){
  pid_t pid = fork();

  if(pid == 0)
    puts("This is a child process\n");
  else {
    printf("ID of the child process: %d\n", pid);
    sleep(30);
  }

  if(pid == 0)
    puts("End Child process\n");
  else
    puts("End Parent process\n");

  return 0;
}
