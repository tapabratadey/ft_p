/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:03:11 by tadey             #+#    #+#             */
/*   Updated: 2018/05/28 13:55:06 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

void	cd_dot_dot(int fd, t_server *server)
{
	char *to_client;

	to_client = "Cannot change from root directory.\nERROR";
	if (ft_strcmp(server->pwd, server->root) == 0)
		send(fd, to_client, ft_strlen(to_client), 0);
	else
	{
		if (chdir(server->root) == 0)
			send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
		else
			send(fd, "ERROR", ft_strlen("ERROR"), 0);
	}
}

void	cd_cd_slash(int fd, t_server *server)
{
	if (ft_strcmp(server->pwd, server->root) == 0)
		send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
	else
	{
		if (chdir(server->root) == 0)
			send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
		else
			send(fd, "ERROR", ft_strlen("ERROR"), 0);
	}
}

void	cd_folder(int fd, t_server *server, char **store)
{
	char	*path;
	char	*folder;
	int		i;

	i = 0;
	while (store[1][i] && store[1][i] != '\n')
		i++;
	folder = ft_strnew(i);
	ft_strncpy(folder, store[1], i);
	char *hold = ft_strjoin(server->root, "/");
	path = ft_strjoin(hold, folder);
	if (chdir(path) == 0)
	{
		getcwd(server->pwd, MAXPATHLEN);
		ft_putstr("Server CWD: ");
		ft_putendl(server->pwd);
		send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
	}
	else
		send(fd, "Not a directory.\nERROR",
		ft_strlen("Not a directory.\nERROR"), 0);
}

void	parse_cd(int fd, t_server *server, char **store)
{
	if ((ft_strcmp(store[0], "cd\n") == 0) || (ft_strcmp(store[1], "/\n") == 0))
		cd_cd_slash(fd, server);
	else if (ft_strcmp(store[1], "..\n") == 0)
		cd_dot_dot(fd, server);
	else
		cd_folder(fd, server, store);
}

#if 0
#include "../inc/server.h"

void	cd_dot_dot(int fd, t_server *server)
{
	char *to_client;

	to_client = "Cannot change from root directory.\nERROR";
	if (ft_strcmp(server->pwd, "/nfs/2017/t/tadey/ft_p") == 0)
		send(fd, to_client, ft_strlen(to_client), 0);
	else
	{
		if (chdir("/nfs/2017/t/tadey/ft_p") == 0)
			send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
		else
			send(fd, "ERROR", ft_strlen("ERROR"), 0);
	}
}

void	cd_cd_slash(int fd, t_server *server)
{
	if (ft_strcmp(server->pwd, "/nfs/2017/t/tadey/ft_p") == 0)
		send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
	else
	{
		if (chdir("/nfs/2017/t/tadey/ft_p") == 0)
			send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
		else
			send(fd, "ERROR", ft_strlen("ERROR"), 0);
	}
}

void	cd_folder(int fd, t_server *server, char **store)
{
	char	*path;
	char	*folder;
	int		i;

	i = 0;
	while (store[1][i] && store[1][i] != '\n')
		i++;
	folder = ft_strnew(i);
	ft_strncpy(folder, store[1], i);
	path = ft_strjoin("/nfs/2017/t/tadey/ft_p/", folder);
	if (chdir(path) == 0)
	{
		getcwd(server->pwd, MAXPATHLEN);
		ft_putstr("Server CWD: ");
		ft_putendl(server->pwd);
		send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
	}
	else
		send(fd, "Not a directory.\nERROR",
		ft_strlen("Not a directory.\nERROR"), 0);
}

void	parse_cd(int fd, t_server *server, char **store)
{
	if ((ft_strcmp(store[0], "cd\n") == 0) || (ft_strcmp(store[1], "/\n") == 0))
		cd_cd_slash(fd, server);
	else if (ft_strcmp(store[1], "..\n") == 0)
		cd_dot_dot(fd, server);
	else
		cd_folder(fd, server, store);
}
#endif
