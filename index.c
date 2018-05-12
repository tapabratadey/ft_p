//server
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clien;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2)
    {
        fprintf(stderr, "Error, No port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Error opening socket\n");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr)); //zeroing the sturture
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Error on binding\n");
    }
    listen(sockfd, 5);
    clien = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clien);
    if (newsockfd < 0)
    {
        printf("Error on accept\n");
    }
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 256);
    if (n < 0)
    {
        printf("Error reading from socket\n");
    }
    printf("Here is the message: %s\n", buffer);
    n = write(newsockfd, "I got your message", 18);
    \  
         if (n < 0)
    {
        printf("Error writing from socket\n");
    }
    return 0;
}

// client
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    char buffer[256];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if (argc < 3)
    {
        fprintf(stderr, "Usage %s hostname port\n", argv[0]);
        exit(1);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Error opening socket\n");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr)); //zeroing the sturture
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        exit(0);
    }
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Error Connecting\n");
    }
    printf("Please enter the message:");
    fgets(buffer, 256, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        printf("Error writing to socket\n");
    }
    n = read(sockfd, buffer, 255);
    \  
             if (n < 0)
    {
        printf("Error reading from socket\n");
    }
    printf("%s\n", buffer);
    return 0;
}