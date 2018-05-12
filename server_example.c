#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>



// create a socket with the socket()
// bind the socket to an address using the bind()
// listen for connections with the listen()
// accept a connection with the accept()
// send and receive data, use the read() and write() system calls

 int main()
 {
    int client_socket; // an int to hold the client socket

    // create a string to hold the data to send to all client
    char server_message[256] = "This is the server. I am your God!";

    // create an integer to hold the retrun value of our socket call
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;

    // family
    server_address.sin_family = AF_INET;

    // port
    server_address.sin_port = htons(9002);

    // ip
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the ip to the port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen to connections
    listen(server_socket, 5);

    // int client socket
    client_socket = accept(server_socket, NULL, NULL);

    // send the message
    // 1st- first pass the socket we are sending data on
    // 2nd- the data that we want to send to the client socket
    // 3rd- size of the server message
    send(client_socket, server_message, sizeof(server_message), 0);

    // close the socket
    close (server_socket);
    return 0; 
 }