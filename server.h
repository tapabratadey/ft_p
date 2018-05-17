/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:30:41 by tadey             #+#    #+#             */
/*   Updated: 2018/05/16 15:30:42 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/param.h>
#include "libft/libft.h"

typedef struct s_server
{
    int server_socket;
    int port;
    int server_accept;
    int ret_recv;
    char *pwd;
}   t_server;


//server
void    server_loop(t_server *server);
void create_client_server(t_server *server);
int error(char *str);
#endif
