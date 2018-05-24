/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:02:18 by tadey             #+#    #+#             */
/*   Updated: 2018/05/23 14:02:19 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client.h"

int error(char *str)
{
    ft_putstr(str);
    exit(0);
}

void if_quit(t_client *client, char *line)
{
    if (ft_strcmp(line, "quit\n") == 0)
    {
        close(client->client_socket);
        error("Disconnected.\n");
    }
}

void clear_buff(char *buf, int size)
{
    int i;

    i = 0;
    while(i < size)
    {
        buf[i] = '\0';
        i++;
    }
}
