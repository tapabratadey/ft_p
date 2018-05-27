/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:30:15 by tadey             #+#    #+#             */
/*   Updated: 2018/05/23 14:02:42 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct	s_client
{
	int		client_socket;
	int		port;
	int		client_connect;
	int		ret_from_server;
	char	*file;

}				t_client;

void			create_client_socket(t_client *client, char *hostname);
int				error(char *str);
void			client_loop(t_client *client);
char			*read_user(char *line);
void			if_quit(t_client *client, char *line);
void			clear_buff(char *buf, int size);
void			client_call(t_client *client);
int				store_file(char **store);
void			open_read(int fd, char **store, t_client *client);
void			save_file(char **store, t_client *client, int *fd, int ret);
void			make_file(char **store, int ret, char *buff);
void			send_to_srv_for_put(char **store, int flag, t_client *client);
void			open_read_send_for_put(t_client *client);
int				check_file_present_empty_for_put(char **store,
				t_client *client);
void			cut_new_line(char **store);
void			recv_from_server(t_client *client, char *buff);
int				max_params(char **store);
int				check_params(char **store);
#endif
