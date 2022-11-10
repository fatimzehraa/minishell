/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:56:03 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:56:04 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "str.h"

int	search_vec_(t_vec *arr, char *name)
{
	int	i;

	i = 0;
	while (arr->content[i])
	{
		if (ft_strncmp(arr->content[i], name, ft_strlen(name)) == 0
			&& (((char *)arr->content[i])[ft_strlen(name)] == '='
			|| ((char *)arr->content[i])[ft_strlen(name)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
