/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 21:50:17 by tadey             #+#    #+#             */
/*   Updated: 2018/05/28 13:55:37 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

void	if_put_helper(char **store, int *fd_open, int fd)
{
	int		i;
	char	*file;

	i = 0;
	while (store[1][i] && store[1][i] != '\n')
		i++;
	file = ft_strnew(i);
	ft_strncpy(file, store[1], i);
	if ((*fd_open = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777)) <= 0)
	{
		send(fd, "ERROR", ft_strlen("ERROR"), 0);
		return ;
	}
}

void	if_put(int fd, char **store, t_server *server)
{
	int		ret;
	char	buff[4096];
	int		fd_open;
	int		ret_empty;

	server->bytes_read = 0;
	ret_empty = 0;
	fd_open = 0;
	ret = 0;
	if_put_helper(store, &fd_open, fd);
	recv(fd, &server->file_len, sizeof(off_t), 0);
	while (server->bytes_read < server->file_len)
	{
		if ((ret = recv(fd, buff, sizeof(buff), 0)) <= 0)
		{
			ft_putstr("fucking error\n");
			break ;
		}
		write(fd_open, buff, ret);
		server->bytes_read += ret;
	}
	send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
}
