/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:57:29 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/12 12:25:39 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "str.h"
#include "token.h"
#include <stdio.h>

int	join_seq(t_str *str, t_list *tks, t_list **plast)
{
	t_list	*cur;
	int		has_space;

	cur = tks;
	has_space = 0;
	while (cur && tk(cur)->type == TOKEN_WORD && !has_space)
	{
		has_space = tk(cur)->has_space;
		if (str_push(str, &tk(cur)->str) == 0)
			return (0);
		cur = delete_cur(cur, free_token);
	}
	(*plast)->next = cur;
	*plast = cur;
	return (1);
}

void	del_empty_var(t_list **tks)
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = *tks;
	while (cur)
	{
		if (tk(cur)->type == TOKEN_VAR
			&& tk(cur)->str.val == NULL)
		{
			tmp = cur;
			cur = cur->next;
			if (prev == NULL)
				*tks = cur;
			else
				prev->next = cur;
			ft_lstdelone(tmp, free_token);
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	join(t_list **tks)
{
	t_list	*cur;

	del_empty_var(tks);
	cur = *tks;
	while (cur)
	{
		if (tk(cur)->type == TOKEN_WORD
			&& tk(cur)->has_space == 0)
		{
			if (join_seq(&tk(cur)->str, cur->next, &cur) == 0)
				return (0);
		}
		else
			cur = cur->next;
	}
	return (1);
}

t_list	*join69(t_list *tks)
{
	t_list	*cur;
	t_list	*head;
	t_str	*str;

	head = tks;
	cur = tks->next;
	str = &tk(tks)->str;
	while (cur)
	{
		str_push(str, &tk(cur)->str);
		cur = cur->next;
	}
	ft_lstclear(&tks->next, free_token);
	return (head);
}
