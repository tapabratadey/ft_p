/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:44:22 by tadey             #+#    #+#             */
/*   Updated: 2018/04/01 07:40:07 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <fcntl.h>
#define BUFF_SIZE 32
#define FD_LIMIT 5000

char	*cut_string(char **arr, int fd)
{
	int		i;
	char	*new_line;
	char	*array;
	char	*new_fd_arr;

	i = 0;
	if (ft_strchr(arr[fd], '\n') == 0 && ft_strlen(arr[fd]) != 0)
	{
		new_line = ft_strjoin(arr[fd], "\n");
		ft_strdel(&arr[fd]);
		arr[fd] = new_line;
	}
	array = arr[fd];
	while (array[i] && array[i] != '\n')
		i++;
	new_line = ft_strnew(i);
	ft_strncpy(new_line, array, i);
	if (ft_strchr(arr[fd], '\n') != 0)
		new_fd_arr = ft_strdup(ft_strchr(arr[fd], '\n') + 1);
	else
		return (ft_strdup(""));
	if (arr[fd] != 0)
		ft_strdel(&arr[fd]);
	arr[fd] = new_fd_arr;
	return (new_line);
}

int		fill_arr(char **arr, int fd)
{
	char	buff[BUFF_SIZE + 1];
	int		read_ret;
	char	*store;

	read_ret = 0;
	while ((read_ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[read_ret] = '\0';
		if (arr[fd] == 0)
			arr[fd] = ft_strdup(buff);
		else
		{
			store = arr[fd];
			arr[fd] = ft_strjoin(arr[fd], buff);
			free(store);
		}
	}
	if (read_ret == 0 && (!arr[fd] || *(arr[fd]) == 0))
		return (0);
	return (1);
}

int		get_next_line(int const fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*arr[FD_LIMIT];
	int			ret_fill_arr;

	if (line == NULL || fd < 0 || read(fd, buff, 0) < 0 || fd > FD_LIMIT)
		return (-1);
	if ((ret_fill_arr = fill_arr(arr, fd)) == 0)
	{
		*line = "";
		return (0);
	}
	*line = cut_string(arr, fd);
	if (ret_fill_arr)
		return (1);
	return (0);
}
