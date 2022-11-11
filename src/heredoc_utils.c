/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:54:57 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/11 14:15:56 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "token.h"
#include "parser.h"

#define FT_TMPFILE "/tmp/minishell-aaaaaa"

void	get_next_comb(char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 1;
	while (i < 7 && s[len - i] == '9')
		s[len - i++] = 'a';
	if ((s[len - i] >= 'a' && s[len - i] < 'z')
		|| (s[len - i] >= '0' && s[len - i] < '9'))
		s[len - i]++;
	else if (s[len - i] == 'z')
		s[len - i] = '0';
}

char	*get_tmp(void)
{
	char	*file;

	file = ft_strndup(FT_TMPFILE, -1);
	if (file == NULL)
		return (NULL);
	while (1)
	{
		if (access(file, F_OK | W_OK | R_OK) == 0)
		{
			get_next_comb(file);
			continue ;
		}
		break ;
	}
	return (file);
}

t_list	*detach_tks(t_list *tks)
{
	t_list	*head;
	t_list	*detach;
	t_list	*next;

	head = tks;
	detach = NULL;
	tks = tks->next;
	while (tks)
	{
		next = tks->next;
		tks->next = NULL;
		ft_lstadd_back(&detach, tks);
		if ((tk(tks)->type & (TOKEN_JOIN | TOKEN_ASTERISK)) == 0)
			break ;
		if (tk(tks)->has_space)
		{
			tks = next;
			break ;
		}
		tks = next;
	}
	head->next = tks;
	return (detach);
}

void	attach(t_list *lst, t_list *node)
{
	t_list	*next;

	next = lst->next;
	lst->next = node;
	ft_lstadd_back(&node, next);
}

int	join_here(t_list *tks)
{
	t_list	*detach;
	t_list	*cur;
	int		is_expandable;

	is_expandable = 1;
	detach = detach_tks(tks);
	cur = detach;
	while (cur)
	{
		if ((tk(cur)->type & (TOKEN_LITERAL | TOKEN_TEMPLATE | TOKEN_ASTERISK)))
			is_expandable = 0;
		cur = cur->next;
	}
	join69(detach);
	tk(detach)->type = TOKEN_WORD;
	attach(tks, detach);
	return (is_expandable);
}
