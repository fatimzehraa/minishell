/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:57:17 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/11 11:39:10 by iait-bel         ###   ########.fr       */
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
	cmd->is_sub_cmd = 0;
	node = ft_lstnew(cmd);
	if (node == NULL)
		free(cmd);
	return (node);
}

t_cmd	*get_cmd(t_list *node)
{
	return ((t_cmd *) node->content);
}

int	build_cmd(t_list	**cmd_head, t_list **cur)
{
	t_list	*cmd;
	t_list	*next;

	cmd = mk_cmd();
	if (cmd == NULL)
		return (0);
	while (*cur && (tk(*cur)->type & TOKEN_PIPE) == 0)
	{
		if (get_cmd(cmd)->is_sub_cmd == 0)
			get_cmd(cmd)->is_sub_cmd = tk(*cur)->type == TOKEN_SUB_CMD;
		if (tk(*cur)->type & TOKEN_RED)
		{
			next = (*cur)->next->next;
			(*cur)->next->next = NULL;
			ft_lstadd_back(&(get_cmd(cmd)->red), *cur);
			*cur = next;
			continue ;
		}
		vec_add(&get_cmd(cmd)->words, tk(*cur)->str.val);
		str_init(&tk(*cur)->str);
		*cur = delete_cur(*cur, free_token);
	}
	ft_lstadd_back(cmd_head, cmd);
	*cur = delete_cur(*cur, free_token);
	return (1);
}

t_list	*filter_cmd(t_list *tks)
{
	t_list	*head;
	t_list	*cur;

	head = NULL;
	cur = tks;
	while (cur)
	{
		if (build_cmd(&head, &cur) == 0)
			return (ft_lstclear(&head, free_cmd),
				ft_lstclear(&tks, free_token), NULL);
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
