/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:52:39 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 14:52:41 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*delete_cur(t_list *list, void (*f)(void *))
{
	t_list	*next;

	if (list == NULL)
		return (NULL);
	next = list->next;
	ft_lstdelone(list, f);
	return (next);
}
