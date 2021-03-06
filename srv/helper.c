/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:03:05 by tadey             #+#    #+#             */
/*   Updated: 2018/05/28 13:55:01 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

int		error(char *str)
{
	ft_putstr(str);
	exit(0);
}

void	clear_buff(char *buf, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		buf[i] = '\0';
		i++;
	}
}

void	error_cases(char **store, int fd)
{
	if ((ft_strcmp(store[0], "ls\n") != 0) &&
	(ft_strcmp(store[0], "pwd\n") != 0) &&
	(ft_strcmp(store[0], "cd\n") != 0) &&
	(ft_strcmp(store[0], "get\n") != 0) &&
	(ft_strcmp(store[0], "put\n") != 0))
		send(fd, "Wrong Command.", ft_strlen("Wrong Command."), 0);
	else if ((ft_strcmp(store[0], "get\n") == 0) && store[1] == NULL)
		send(fd, "Usage: get <file>", ft_strlen("Usage: get <file>"), 0);
	else if ((ft_strcmp(store[0], "put\n") == 0) && store[1] == NULL)
		send(fd, "Usage: put <file>", ft_strlen("Usage: put <file>"), 0);
}
