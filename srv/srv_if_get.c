/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 21:50:34 by tadey             #+#    #+#             */
/*   Updated: 2018/05/28 13:55:31 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.h"

void	cut_new_line(char **store, char **file)
{
	int i;

	i = 0;
	while (store[1][i] && store[1][i] != '\n')
		i++;
	*file = ft_strnew(i);
	ft_strncpy(*file, store[1], i);
}

int		read_loop(int *fd_open, int *counter, int fd, int *ret)
{
	char	buff[4096];
	int		fd_stat;

	fd_stat = 0;
	counter = 0;
	while ((*ret = read(*fd_open, buff, 4096)) > 0)
	{
		send(fd, buff, *ret, 0);
		if (*ret < 4096)
			return (0);
	}
	return (1);
}

void	if_get(int fd, char **store)
{
	char	*file;
	int		fd_open;
	int		counter;
	int		ret;

	ret = 0;
	counter = 0;
	fd_open = 0;
	file = NULL;
	cut_new_line(store, &file);
	if ((fd_open = open(file, O_RDONLY)) < 0)
	{
		send(fd, "Couldn't open file.\n",
		ft_strlen("Couldn't open file.\n"), 0);
		return ;
	}
	else if ((read_loop(&fd_open, &counter, fd, &ret)) == 0)
		return ;
	send(fd, "Fuck empty files.", ft_strlen("Fuck empty files."), 0);
}
