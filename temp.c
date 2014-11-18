#include <stdio.h>
#include <sys/socket.h>

int main(void){
  printf("%d\n", PF_INET);
  printf("%d\n", PF_INET6);
  printf("%d\n", PF_LOCAL);
  printf("%d\n", PF_PACKET);
  printf("%d\n", PF_IPX);
  printf("%d\n", SOCK_STREAM);
  printf("%d\n", SOCK_DGRAM);
  printf("%d\n", IPPROTO_TCP);
  printf("%d\n", IPPROTO_UDP);




}
