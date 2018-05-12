#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


// create a socket with the socket()
// connect the socket to the address of the server using the connect() system call
// send and receive data, use the read() and write() system calls.

int main()
{
    // create a socket
    int network_socket;


    int connect_status;

    // 1st param- domain of socket, since it is an internet socket pass AF_INET
    // 2nd param- type of the socket, which is a TCP socket (connection socket)
    // 3rd param- protocol, 0 as a default protocol
    // this creates the network socket (client) one of the side
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    struct sockaddr_in server_address;

    // set the family of the address so it knows what type of address we are working with
    server_address.sin_family = AF_INET;

    // specify the port we need to connect to
    // we could pass the port in as an integer but the data format is different from the structure
    // so we need to use a conversion function, which is going to convert the integer port passed
    // in into the right network byte order called htons
    // pass in a port that we can use remortely
    server_address.sin_port = htons(9002);

    // now we need to specify the IP address 
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    // now we can connect, calling the connect function which returns an integer
    // 1st param- is our socket
    // 2nd param- cast our server address struct to sockaddr and pass the address
    // 3rd param- size of the address use the sizeof();
    connect_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    
    // check for error with the connection
    if (connect_status == -1)
        printf("there was an error connecting to the remote socket.\n");
    
    //recieve data
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // print out the server's response
    printf("The server sent the data: %s\n", server_response);

    // close the socket
    close(network_socket);
    return 0;
}