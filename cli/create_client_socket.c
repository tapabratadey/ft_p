/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_client_socket.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:02:06 by tadey             #+#    #+#             */
/*   Updated: 2018/05/23 14:02:09 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client.h"

void create_client_socket(t_client *client, char *hostname)
{
    // struct that deals with internet addresses
    struct sockaddr_in serv_addr;
    int optval;
    socklen_t optlen;
    int client_running;

    optlen = sizeof(optval);
    client_running = 1;

    // create a socket
    client->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->client_socket < 0)
        error("Couldn't create a socket.\n");
    printf("Client socket is created...\n");

    // set keep alive on
    optval = 1;
    optlen = sizeof(optval);

    // specify structure values
    serv_addr.sin_family = AF_INET; //refers to addresses from the internet
    serv_addr.sin_port = htons(client->port);

    // converts IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, hostname, &serv_addr.sin_addr) <= 0)
        error("Check your address.\n");

    // connect
    if ((client->client_connect = connect(client->client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
        error("Couldn't Connect\n");
    printf("Connected to Server.\n\n");
    while(client_running)
        client_call(client);
}
