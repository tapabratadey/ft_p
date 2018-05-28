/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:30:41 by tadey             #+#    #+#             */
/*   Updated: 2018/05/23 14:02:53 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct		s_server
{
	int		server_socket;
	int		port;
	int		ret_recv;
	char	*pwd;
	char	*if_ls;
	char	*read_buff;
	off_t	file_len;
	off_t	bytes_read;
}					t_server;

void				server_loop(t_server *server);
void				create_client_server(t_server *server);
int					error(char *str);
void				if_ls(int fd);
void				if_pwd(int fd);
void				create_client_server(t_server *server);
void				parse_cd(int fd, t_server *server, char **store);
void				clear_buff(char *buf, int size);
void				error_cases(char **store, int fd);
void				if_put(int fd, char **store, t_server *server);
void				if_get(int fd, char **store);
void				get_from_client(t_server *server, int fd);
#endif
