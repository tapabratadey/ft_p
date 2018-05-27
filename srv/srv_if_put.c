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
	off_t	file_len;
	off_t	nb_rxb;
	// char	*line;
	// char	*old_line;

	// line = (char *)malloc(sizeof(char*));
	ret_empty = 0;
	fd_open = 0;
	ret = 0;
	if_put_helper(store, &fd_open, fd);
	recv(fd, &file_len, sizeof (off_t), 0);

	for (nb_rxb = 0; nb_rxb < file_len; nb_rxb += ret)
	{
		ret = recv(fd, buff, sizeof (buff), 0);
		if (ret <= 0)
		{
			ft_putstr("fucking error\n");
			break;
		}
		write(fd_open, buff, ret);
	}
	close(fd_open);

#if 0
	while ((ret = recv(fd, buff, 4096, 0)) >= 0)
	{
		buff[ret] = '\0';
		if ((ft_strcmp(buff, "empty")) == 0)
		{
			send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
			clear_buff(buff, 4096);
			return ;
		}
		#if 0
		old_line = line;
		line = ft_strjoin(line, buff);
		free(old_line);
		#endif
		if (ret < 4096)
			break ;
		write(fd_open, buff, ret);
	}
#endif
	send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
}
