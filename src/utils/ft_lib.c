/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:56:22 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:56:23 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_realloc(void *mem, int size, int append)
{
	char	*from;
	char	*to;
	int		i;

	from = (char *)mem;
	to = malloc(sizeof(void *) * (size + append));
	if (to == NULL)
		return (NULL);
	i = 0;
	while (i < (size * 8))
	{
		to[i] = from[i];
		i++;
	}
	free(mem);
	return (to);
}
