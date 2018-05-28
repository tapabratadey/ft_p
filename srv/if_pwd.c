/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:03:29 by tadey             #+#    #+#             */
/*   Updated: 2018/05/28 13:55:18 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

void	if_pwd(int fd)
{
	char *current_cwd;

	current_cwd = NULL;
	current_cwd = getcwd(current_cwd, MAXPATHLEN);
	send(fd, current_cwd, ft_strlen(current_cwd), 0);
}
