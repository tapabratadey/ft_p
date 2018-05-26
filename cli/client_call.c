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

void	prompts(char **line, char ***store, t_client *client)
{
	*(line) = ft_strnew(1);
	ft_putstr("->");
	*(line) = read_user(*line);
	if_quit(client, *line);
	*(store) = ft_strsplit(*line, ' ');
}

void	send_cmd_to_serv(char *line, int flag, t_client *client)
{
	if (line && flag == 0)
	{
		if (send(client->client_socket, line, ft_strlen(line), 0) <= 0)
			return ;
	}
}

void	send_to_srv_for_get(char **store, t_client *client)
{
	int fd;
	int ret;

	fd = 0;
	ret = 0;
	if (ft_strcmp(store[0], "get") == 0)
		save_file(store, client, fd, ret);
}

void	parse_cmd(char *line, int flag, t_client *client, char **store)
{
	send_cmd_to_serv(line, flag, client);
	send_to_srv_for_put(store, flag, client);
	send_to_srv_for_get(store, client);
}

void	client_call(t_client *client)
{
	char	*line;
	char	**store;
	int		flag;
	char	buff[4096];

	line = NULL;
	store = NULL;
	flag = 0;
	prompts(&line, &store, client);
	if ((check_params(store)) == 0)
		return ;
	else if ((ft_strcmp(store[0], "put")) == 0)
	{
		if ((check_file_present_empty_for_put(store, client)) == 0)
			flag = 1;
	}
	parse_cmd(line, flag, client, store);
	if ((flag == 0) && (ft_strcmp(store[0], "get") != 0))
	{
		recv_from_server(client, buff);
		buff[client->ret_from_server] = '\0';
		printf("%s\n", buff);
		clear_buff(buff, 4096);
	}
}
