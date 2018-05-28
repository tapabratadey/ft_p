/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 13:47:49 by tadey             #+#    #+#             */
/*   Updated: 2018/05/28 13:54:28 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"

int		empty_file(char *buff, int fd, char **store)
{
	int		i;
	char	*file;

	i = 0;
	while (store[1][i] && store[1][i] != '\n')
		i++;
	file = ft_strnew(i);
	ft_strncpy(file, store[1], i);
	if (ft_strcmp("Fuck empty files.", buff) == 0)
	{
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		clear_buff(buff, 4096);
		return (0);
	}
	return (1);
}

int		cant_open(char *buff)
{
	if ((ft_strcmp(buff, "Couldn't open file.\n") == 0))
	{
		ft_putstr("Couldn't open file.\n");
		clear_buff(buff, 4096);
		return (0);
	}
	return (1);
}

void	if_put_helper(char **store, int *fd)
{
	int		i;
	char	*file;

	i = 0;
	while (store[1][i] && store[1][i] != '\n')
		i++;
	file = ft_strnew(i);
	ft_strncpy(file, store[1], i);
	if ((*fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777)) < 0)
	{
		ft_putstr("Error in opening file.\n");
		return ;
	}
}

void	save_file(char **store, t_client *client)
{
	char	buff[4096];
	int		fd;
	int		ret;
	int		counter;

	fd = 0;
	ret = 0;
	counter = 0;
	ret = 0;
	while ((ret = recv(client->client_socket, buff, 4096, 0)) >= 0)
	{
		buff[ret] = '\0';
		if ((empty_file(buff, fd, store)) == 0)
			break ;
		else if (cant_open(buff) == 0)
			return ;
		else if (counter == 0)
			if_put_helper(store, &fd);
		write(fd, buff, ret);
		if (ret < 4096)
			break ;
		counter++;
	}
	ft_putstr("SUCCESS\n");
}
