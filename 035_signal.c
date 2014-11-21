#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig){
  if(sig == SIGALRM)
    puts("Time out!!");
  alarm(2);
}

void keycontrol(int sig){
  if(sig == SIGINT)
    puts("CTRL+C is pressed.");
}

int main(int argc, char *argv[]){
  int i;
  signal(SIGALRM, timeout);
  signal(SIGINT, keycontrol);
  alarm(10);

  for(i=0; i<10; i++){
    puts("wait...");
    sleep(10);
  }  

  return 0;
}
