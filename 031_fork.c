#include <stdio.h>
#include <unistd.h>

int glovalVal = 10;

int main(int argc, char * argv[]){
  pid_t pid;
  int localVal = 20;
  glovalVal++, localVal += 5;

  pid = fork();

  if(pid == 0)
    glovalVal += 2, localVal +=2;
  else
    glovalVal -= 2, localVal -=2;

  
  if(pid == 0)
    printf("Chile proc: %d, %d\n", glovalVal, localVal);
  else
    printf("Parent proc: %d, %d\n", glovalVal, localVal);

  return 0;
}
