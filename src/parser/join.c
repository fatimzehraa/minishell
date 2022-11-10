/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:57:29 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:57:31 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "str.h"
#include "token.h"

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

int	join(t_list *tks)
{
	t_list	*cur;

	cur = tks;
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
