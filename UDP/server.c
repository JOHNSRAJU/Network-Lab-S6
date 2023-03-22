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
 
  int sockfd;
  struct sockaddr_in server_addr, client_addr;
  char buffer[1024];
  char str[1024];
  socklen_t addr_size;
  int n;
 
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("[-]socket error");
    exit(1);
  }
 
  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  n = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0){
    perror("[-]bind error");
    exit(1);
  }
 printf("Server created successfully !\n");
 while(1){
  bzero(buffer, 1024);
  addr_size = sizeof(client_addr);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
  printf("[+]Data recv: %s\n", buffer);
  if(strcmp(buffer,"exit")==0){
    exit(0);
  }
  printf("Enter a message :-");
  bzero(buffer, 1024);
  scanf("%s",str);
  strcpy(buffer, str);
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
  printf("[+]Data send: %s\n", buffer);
  if(strcmp(str,"exit")==0){
    exit(0);
  }
 }
  return 0;
}