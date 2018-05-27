/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 13:47:49 by tadey             #+#    #+#             */
/*   Updated: 2018/05/25 13:47:50 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client.h"

#if 0
void	cut_new_line_get(char **store, char **file)
{
	int i;

	i = 0;
	while (store[1][i] && store[1][i] != '\n')
		i++;
	*file = ft_strnew(i);
	ft_strncpy(*file, store[1], i);
}

void	make_file(char **store, int ret, char *buff)
{
	char	*file;
	int		fd;
	int		i;

	i = 0;
	fd = 0;
	cut_new_line_get(store, &file);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (buff)
		write(fd, buff, ret);
	clear_buff(buff, 4096);
	ft_putstr("SUCCESS\n");
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

int		empty_file(char *buff, int fd, char *file)
{
	if (ft_strcmp("Fuck empty files.", buff) == 0)
	{
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		ft_putstr("SUCCESS\n");
		clear_buff(buff, 4096);
		return (0);
	}
	return (1);
}

void	save_file(char **store, t_client *client, int fd, int ret)
{
	int		i;
	char	*file;
	char	buff[4096];

	i = 0;
	cut_new_line_get(store, &file);
	while ((ret = recv(client->client_socket, buff, 4096, 0)) > 0)
	{
		buff[ret] = '\0';
		if (cant_open(buff) == 0)
			break ;
		else if ((empty_file(buff, fd, file)) == 0)
			break ;
		else
		{
			make_file(store, ret, buff);
			clear_buff(buff, 4096);
			break ;
		}
		clear_buff(buff, 4096);
	}
}

#endif
void	if_put_helper(char **store, int *fd)
{
	int		i;
	char	*file;

	i = 0;
	while (store[1][i] && store[1][i] != '\n')
		i++;
	file = ft_strnew(i);
	ft_strncpy(file, store[1], i);
	if ((*fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777)) <= 0)
	{
		ft_putstr("fucking error.\n");
		return ;
	}
}

void	save_file(char **store, t_client *client, int *fd, int ret)
{
	// int		ret;
	char	buff[4096];
	int		ret_empty;
	off_t	file_len;
	off_t	bytes_read;

	bytes_read = 0;
	ret_empty = 0;

	ret = 0;
	if_put_helper(store, &fd);
	recv(client->client_socket, &file_len, sizeof (off_t), 0);
	ft_putstr("tapa\n");
	printf("file_len: %lld", file_len);
	while (bytes_read < file_len)
	{
		if ((ret = recv(client->client_socket, buff, sizeof (buff), 0)) <= 0)
		{
			ft_putstr("fuckin error\n");
			break;
		}
		ft_putstr(buff);
		write(fd, buff, ret);
		bytes_read += ret;
	}
	send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
}
