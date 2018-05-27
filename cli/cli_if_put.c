/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 13:48:03 by tadey             #+#    #+#             */
/*   Updated: 2018/05/25 13:48:04 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client.h"

#include <sys/stat.h>

void	cut_new_line_put(char **store, t_client *client)
{
	int i;

	i = 0;
	while (store[1][i] && store[1][i] != '\n')
		i++;
	client->file = ft_strnew(i);
	ft_strncpy(client->file, store[1], i);
}

int		check_file_present_empty_for_put(char **store, t_client *client)
{
	int	fd_open;
	int	read_ret;

	read_ret = 0;
	fd_open = 0;
	cut_new_line_put(store, client);
	if ((fd_open = open(client->file, O_RDONLY)) < 0)
	{
		ft_putstr("Error in opening file.\n");
		return (0);
	}
	return (1);
}

void	open_read_send_for_put(t_client *client)
{
	int		fd;
	char	buff[4096];
	int		ret;
	int			fd_empty;
	struct stat	st;



	fd_empty = 0;
	ret = 0;
	fd = 0;
	if ((fd = open(client->file, O_RDONLY)) < 0)
	{
		ft_putstr("Couldn't open file.\n");
		return ;
	}
	else
	{
		fstat(fd, &st);
		send(client->client_socket, &st.st_size, sizeof (off_t), 0);
		while ((ret = read(fd, buff, 4096)) > 0)
			send(client->client_socket, buff, ret, 0);
	}
}

void	send_to_srv_for_put(char **store, int flag,
	t_client *client)
{
	if ((ft_strcmp(store[0], "put") == 0) && flag == 0)
		open_read_send_for_put(client);
}
