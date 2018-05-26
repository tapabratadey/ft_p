/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 21:50:17 by tadey             #+#    #+#             */
/*   Updated: 2018/05/25 21:50:18 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.h"

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

void	if_put(int fd, char **store)
{
	int		ret;
	char	buff[4096];
	int		fd_open;
	int		ret_empty;

	ret_empty = 0;
	fd_open = 0;
	ret = 0;
	if_put_helper(store, &fd_open, fd);
	while ((ret = recv(fd, buff, 4096, 0)) >= 0)
	{
		buff[ret] = '\0';
		if ((ft_strcmp(buff, "empty")) == 0)
		{
			send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
			clear_buff(buff, 4096);
			return ;
		}
		if (ret < 4096)
			break ;
		write(fd_open, buff, ret);
	}
	send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
}
