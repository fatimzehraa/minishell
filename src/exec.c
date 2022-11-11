/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:13:03 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/11 14:09:51 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include "list.h"
#include "str.h"
#include "token.h"
#include "parser.h"
#include "minishell.h"
#include "exec.h"
#include "vector.h"

t_list	*ignore(t_list *tokens)
{
	while (!(tk(tokens)->type & TOKEN_LIST))
		tokens = tokens->next;
	return (tokens);
}

t_list	*detach(t_list *tokens)
{
	t_list	*last;

	last = NULL;
	while (tokens && !(tk(tokens)->type & TOKEN_LIST))
	{
		last = tokens;
		tokens = tokens->next;
	}
	last->next = NULL;
	return (tokens);
}

void	free_cmd(void *ptr)
{
	t_cmd	*cmd;

	cmd = ptr;
	free_vec(&cmd->words);
	ft_lstclear(&cmd->red, free_token);
	free(ptr);
}

int	and_or(t_list *tokens, t_ctx *ctx)
{
	t_list	*cmds;
	t_list	*last;

	switch_handler(ctx);
	while (tokens && !(tk(tokens)->type & TOKEN_EOL))
	{
		last = detach(tokens);
		cmds = parser(tokens, ctx);
		if (cmds == NULL)
			return (switch_handler(ctx), ft_lstclear(&last, free_token), 0);
		if (execute(cmds, ctx) == 0)
			return (switch_handler(ctx), ft_lstclear
				(&cmds, free_cmd), ft_lstclear(&last, free_token), 0);
		ft_lstclear(&cmds, free_cmd);
		if (g_exit_status != 0 && last && tk(last)->type == TOKEN_AND)
			last = ignore(last->next);
		else if (g_exit_status == 0 && last && tk(last)->type == TOKEN_OR)
			last = ignore(last->next);
		if(last)
			tokens = last->next;
		else
			tokens = NULL;
	}
	ft_lstclear(&tokens, free_token);
	switch_handler(ctx);
	return (1);
}

void	exec_line(char *line, t_ctx *ctx)
{
	t_list	*tokens;

	while (is_space(*line))
		line++;
	tokens = tokenizer(line);
	if (tokens == NULL || tk(tokens)->type == TOKEN_EOL)
		return ;
	if (!check_syntax(tokens))
	{
		ft_putstr(2, "minishell: syntax error\n");
		g_exit_status = 258;
		return ;
	}
	read_heredocs(ctx, tokens);
	and_or(tokens, ctx);
}
