/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:13:03 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/09 18:21:11 by fael-bou         ###   ########.fr       */
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


t_list	*ignore(t_list *tokens)
{
	while (!(tk(tokens)->type & TOKEN_LIST))
		tokens = tokens->next;
	return (tokens);
}


t_list *detach(t_list *tokens)
{
	t_list *last;

	last = NULL;
	while (!(tk(tokens)->type & TOKEN_LIST))
	{
		last = tokens;
		tokens = tokens->next;
	}
	last->next = NULL;
	return tokens;
}

void	and_or(t_list *tokens, t_ctx *ctx)
{
	t_list	*cmds;
	t_list	*last;

	switch_handler(ctx);
	while (tokens)
	{
		last = detach(tokens);
		cmds = parser(tokens, ctx);
		execute(cmds, ctx);
		if (exit_status != 0 && tk(last)->type == TOKEN_AND)
			last = ignore(last->next);
		else if (exit_status == 0 && tk(last)->type == TOKEN_OR)
			last = ignore(last->next);
		tokens = last->next;
	}
	switch_handler(ctx);
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
		exit_status = 258;
		return ;
	}
	read_heredocs(ctx, tokens);
	// handel logic .. && ||
	and_or(tokens, ctx);
}
