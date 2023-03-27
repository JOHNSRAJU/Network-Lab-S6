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
void func(int sockfd){
    char buff[MAX];
    int n = 0, wSize, ack, j, i = 0;
    printf("Enter the data: ");
    bzero(buff, 1024);
    while ((buff[n++] = getchar()) != '\n');
    printf("Enter the window size: ");
    scanf("%d", &wSize);
    write(sockfd, &wSize, sizeof(wSize));
    n = 0;
    while(1) {
        // Send window of data
        for (j = 0; j < wSize; j++) {
            write(sockfd, &buff[i], sizeof(buff[i]));
            if (buff[i]=='\n') {
                break;
            }
            i++;
        }
        // Wait for acknowledgement
        sleep(wSize);
        read(sockfd, &ack, sizeof(ack));
        printf("Received acknowledgement: %d\n", ack);
        i=ack+1;
        // If acknowledgement is greater than or equal to the total data length, exit loop
        if ((buff[i]=='\n')){
            printf("Successfully finished\n");
            break;
        }
    }
}
int main(){
    int sockfd;
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Connect to server
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection with the server failed\n");
        exit(0);
    }
    else {
        printf("Connected to the server\n");
    }
    // Call function to implement Go-Back-N protocol
    func(sockfd);

    // Close the socket
    close(sockfd);
}
