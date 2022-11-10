/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:57:03 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:57:04 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

int	str_same(t_str *s1, t_str *s2, int s2_size)
{
	int	i;

	i = 0;
	while (i < s2_size)
	{
		if (s1->val[i] != s2->val[i])
			return (0);
		i++;
	}
	return (1);
}

int	str_clone(t_str *dest, t_str *src)
{
	char	*tmp;

	if (src->size < dest->size)
	{
		ft_strncpy(dest->val, src->val, src->size);
		dest->size = src->size;
		return (1);
	}
	tmp = ft_strndup(src->val, src->size);
	free(dest->val);
	str_init(dest);
	if (tmp == NULL)
		return (0);
	dest->val = tmp;
	dest->size = src->size;
	dest->cap = src->size;
	return (1);
}

int	str_pnclone(t_str *dest, char *src, int n)
{
	t_str	s;

	s.val = src;
	if (n == -1)
		s.size = ft_strlen(src);
	else
		s.size = n;
	s.cap = s.size;
	return (str_clone(dest, &s));
}

int	str_psame(t_str *dest, char *src, int len)
{
	t_str	s;

	s.val = src;
	s.size = len;
	s.cap = s.size;
	return (str_same(dest, &s, len));
}

void	str_free(t_str *s)
{
	free(s->val);
	str_init(s);
}
