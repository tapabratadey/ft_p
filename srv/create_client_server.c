/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_client_server.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:03:00 by tadey             #+#    #+#             */
/*   Updated: 2018/05/23 14:03:01 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.h"

void create_client_server(t_server *server)
{
    struct sockaddr_in serv_addr;
    if ((server->server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("Couldn't create a socket.\n");
    printf("Server socket is created...\n");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(server->port);
    if (bind(server->server_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        printf("%s", strerror(errno));
        error("Couldn't bind to port.\n");
    }
    printf("Connected to port...\n");
    server_loop(server);
}
