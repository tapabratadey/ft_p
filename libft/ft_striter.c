/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 15:50:31 by tadey             #+#    #+#             */
/*   Updated: 2017/12/08 16:17:24 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**applies the func f to each char in the char string s.
*/

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	if (s && f)
	{
		while (*s)
		{
			f(s);
			s++;
		}
	}
}
