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

void	recv_from_client(int fd, t_server *server, char *buff)
{
	while ((server->ret_recv = recv(fd, buff, 4096, 0)) <= 0)
		;
	printf("Bytes received: %d\n", server->ret_recv);
	buff[server->ret_recv] = '\0';
	printf("Client command: %s\n", buff);
}

void	parsing(char **store, int fd, t_server *server, char *buff)
{
	getcwd(server->pwd, MAXPATHLEN);
	if ((ft_strcmp(store[0], "put") == 0) && store[1] != NULL)
		if_put(fd, store);
	else if ((ft_strcmp(store[0], "get") == 0) && store[1] != NULL)
		if_get(fd, store);
	else if ((ft_strcmp(store[0], "cd") == 0) ||
	(ft_strcmp(store[0], "cd\n") == 0))
		parse_cd(fd, server, store);
	else if (ft_strcmp("pwd\n", buff) == 0)
		if_pwd(fd);
	else if (ft_strcmp("ls\n", buff) == 0)
		if_ls(fd);
	else
		error_cases(store, fd);
	ft_putstr("Done with child.\n");
}

void	get_from_client(t_server *server, int fd)
{
	char	buff[4096];
	char	**store;
	int		i;

	i = 0;
	recv_from_client(fd, server, buff);
	store = ft_strsplit(buff, ' ');
	parsing(store, fd, server, buff);
	ft_putstr("Done with child.\n");
	clear_buff(buff, 4096);
}
