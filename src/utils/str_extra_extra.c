/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extra_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:56:11 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/12 15:06:29 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"

int	ft_putstr(int fd, char *s)
{
	return (write(fd, s, ft_strlen(s)));
}

int	is_space(char a)
{
	if (a == '\t' || a == '\n' || a == '\v'
		|| a == '\f' || a == '\r' || a == ' ')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_isnum(int c)
{
	return (c >= '0' && c <= '9');
}

int	str_ppsame(t_str *s1, char *s2, int s2_size)
{
	int	i;

	(void) s2_size;
	i = 0;
	while (i < s1->size)
	{
		if (s1->val[i] != s2[i])
			return (-1);
		i++;
	}
	return (i);
}
