/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:57:17 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 20:30:49 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "parser.h"
#include "minishell.h"
#include "cmd.h"
#include "str.h"
#include "token.h"
#include "vector.h"
#include <stdio.h>

t_list	*mk_cmd(void)
{
	t_list	*node;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->red = NULL;
	init_vec(&cmd->words, 20);
	node = ft_lstnew(cmd);
	if (node == NULL)
		free(cmd);
	return (node);
}

t_cmd	*get_cmd(t_list *node)
{
	return ((t_cmd *) node->content);
}

void	_filter(t_list **next, t_list **cur, t_list *cmd)
{
	*next = (*cur)->next->next;
	(*cur)->next->next = NULL;
	ft_lstadd_back(&(get_cmd(cmd)->red), *cur);
	*cur = *next;
}

t_list	*filter_cmd(t_list *tks)
{
	t_list	*head;
	t_list	*cur;
	t_list	*cmd;
	t_list	*next;

	head = NULL;
	cur = tks;
	while (cur)
	{
		cmd = mk_cmd();
		while (cur && (tk(cur)->type & TOKEN_PIPE) == 0)
		{
			if (tk(cur)->type & TOKEN_RED)
			{
				_filter(&next, &cur, cmd);
				continue ;
			}
			vec_add(&get_cmd(cmd)->words, tk(cur)->str.val);
			str_init(&tk(cur)->str);
			cur = delete_cur(cur, free_token);
		}
		ft_lstadd_back(&head, cmd);
		cur = delete_cur(cur, free_token);
	}
	return (head);
}

t_list	*parser(t_list *tokens, t_ctx *ctx)
{
	if (!expand(tokens, ctx))
		return (NULL);
	if (!join(tokens))
		return (NULL);
	return (filter_cmd(tokens));
}
