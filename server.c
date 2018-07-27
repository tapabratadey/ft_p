/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:30:27 by tadey             #+#    #+#             */
/*   Updated: 2018/05/28 13:54:10 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/server.h"

void	server_loop(t_server *server)
{
	int					cli_fd;
	struct sockaddr_in	cli_addr;
	socklen_t			addr_len;
	int					in_client;

	listen(server->server_socket, 10);
	in_client = 1;
	addr_len = sizeof(cli_addr);
	while (1)
	{
		if ((cli_fd = accept(server->server_socket,
		(struct sockaddr *)&cli_addr, &addr_len)) < 0)
			error("Couldn't accept connection.\n");
		printf("Connection accepted.\n\n");
		server->root = getdir();
		printf ("dir: %s\n", server->root);
		if (fork() == 0)
		{
			ft_putendl("Forking for client");
			while (in_client)
				get_from_client(server, cli_fd);
		}
	}
}

void	create_client_server(t_server *server)
{
	struct sockaddr_in serv_addr;

	if ((server->server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Couldn't create a socket.\n");
	printf("Server socket is created...\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(server->port);
	if (bind(server->server_socket, (struct sockaddr *)&serv_addr,
	sizeof(serv_addr)) == -1)
	{
		printf("%s", strerror(errno));
		error("Couldn't bind to port.\n");
	}
	printf("Connected to port...\n");
	server_loop(server);
}

int		main(int argc, char **argv)
{
	t_server *server;

	server = (t_server *)malloc(sizeof(t_server));
	if (argc != 2)
		error("Usage: ./server <port>\n");
	server->port = ft_atoi(argv[1]);
	create_client_server(server);
	close(server->server_socket);
	return (0);
}
