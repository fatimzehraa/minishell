/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:56:15 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:56:17 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "str.h"
#include "utils.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char	*ft_strjoin(char *s1, char *s2, int s2_len)
{
	int		s1_len;
	char	*str;

	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	if (s2_len == -1)
		s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 1);
	if (str == 0)
	{
		free(s1);
		return (0);
	}
	ft_strncpy(str, s1, s1_len);
	ft_strncpy(str + s1_len, s2, s2_len);
	free(s1);
	return (str);
}

int	ft_append(char *dest, char *src, int len)
{
	int	i;

	while (*dest)
		dest++;
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

int	til_set(char *str, char *set, int n)
{
	int	i;

	i = 0;
	while (i < n && str[i] && !has_chars(str[i], set))
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	char	a;
	int		i;

	a = (char)c;
	i = 0;
	if (a == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == a)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
