/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:56:31 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:56:32 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

int	until(char *str, char *limits)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(limits, str[i]))
			break ;
		i++;
	}
	return (i);
}

int	get_next_word(t_str *str, char **s_ptr)
{
	char	*s;

	s = *s_ptr;
	str_init(str);
	if (s == NULL)
	{
		str->val = NULL;
		return (0);
	}
	str->size = until(s, " \t\r\n\f");
	str->cap = str->size;
	str->val = ft_strndup(s, str->size);
	s += str->size;
	while (is_space(*s))
		s++;
	*s_ptr = s;
	return (str->val != NULL);
}
