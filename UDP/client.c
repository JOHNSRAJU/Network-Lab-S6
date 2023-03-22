#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int n;
  int sockfd;
  struct sockaddr_in addr;
  char buffer[1024];
  char str[1024];
  socklen_t addr_size;
 
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);

  printf("Client created successfully !\n");
while(1){
  printf("Enter a message :-");
  bzero(buffer, 1024);
  n=0;
  while ((buffer[n++] = getchar()) != '\n');
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
  printf("[+]Data send: %s\n", buffer);
  if(strcmp(buffer,"exit\n")==0){
    exit(0);
  }
  bzero(buffer, 1024);
  addr_size = sizeof(addr);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
  printf("[+]Data recv: %s\n", buffer);
  if(strcmp(buffer,"exit\n")==0){
    exit(0);
  }
}
  return 0;
}