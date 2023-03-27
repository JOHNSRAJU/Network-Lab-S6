#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX 1024
#define PORT 8080
#define SA struct sockaddr
// Function to implement Go-Back-N protocol
void func(int connfd)
{
    char buff[MAX];
    int n = 0, wSize, ack, j, i = 0;
    read(connfd, &wSize, sizeof(wSize));
    printf("Window size: %d\n", wSize);
    bzero(buff,1024);
    while(1) {
        // Receive window of data
        for (j = 0; j < wSize; j++) {
            read(connfd, &buff[i], sizeof(buff[i]));
            if (buff[i]=='\n') {
                break;
            }
            i++;
        }
        // Send acknowledgement
        ack = i-1;
        write(connfd, &ack, sizeof(ack));
        sleep(wSize);
        printf("[+]Data received upto :-%s \n",buff);
        // If end of data reached, exit loop
        if (buff[i] == '\n') {
            printf("Received data: %s\n", buff);
            printf("Successfully finished\n");
            break;
        }
    }
}
int main(){
    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cli;
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    }
    else {
        printf("Socket successfully created\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    // Bind the socket with the server address and check for errors
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed\n");
        exit(0);
    }
    else {
        printf("Socket successfully binded\n");
    }
    // Now server is ready to listen and verify
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed\n");
        exit(0);
    }
    else {
        printf("Server listening\n");
    }
    len = sizeof(cli);
    // Accept the data packet from client and verify
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Server accept failed\n");
        exit(0);
    }
    else {
        printf("Server accepted the client\n");
    }
    // Call function to implement Go-Back-N protocol
    func(connfd);
    // Close the sockets
    close(sockfd);
    close(connfd);
}
