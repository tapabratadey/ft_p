/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 10:01:20 by tadey             #+#    #+#             */
/*   Updated: 2018/05/28 13:53:33 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/client.h"

void	recv_from_server(t_client *client, char *buff)
{
	if ((client->ret_from_server = recv(client->client_socket, buff,
	4096, 0)) <= 0)
	{
		printf("%d", client->ret_from_server);
		error("Couldn't receive a response from server.\n");
		return ;
	}
}

void	create_client_socket(t_client *client, char *hostname)
{
	struct sockaddr_in serv_addr;

	client->client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client->client_socket < 0)
		error("Couldn't create a socket.\n");
	printf("Client socket is created...\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(client->port);
	if (inet_pton(AF_INET, hostname, &serv_addr.sin_addr) <= 0)
		error("Check your address.\n");
	if ((client->client_connect = connect(client->client_socket,
		(struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
		error("Couldn't Connect\n");
	printf("Connected to Server.\n\n");
	while (1)
		client_call(client);
}

int		main(int argc, char **argv)
{
	t_client *client;

	client = (t_client *)malloc(sizeof(t_client));
	client->port = ft_atoi(argv[2]);
	if (argc != 3)
		error("Usage: ./client <host machine> <port>\n");
	while (1)
	{
		create_client_socket(client, argv[1]);
		close(client->client_socket);
	}
	return (0);
}
