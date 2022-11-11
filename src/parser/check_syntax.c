/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:15:16 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/11 13:29:20 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "list.h"
#include "minishell.h"
#include "parser.h"
#include "token.h"

int	is_special_token(t_token *token)
{
	if (token->type == TOKEN_PIPE || token->type == TOKEN_AND
		|| token->type == TOKEN_OR)
		return (1);
	return (0);
}

int	check_if_followed(t_list *tokens)
{
	return (is_special_token(tk(tokens))
		&& (is_special_token(tk(tokens->next))
			|| tokens->next == NULL));
}

int	check_redirections(t_list *tokens)
{
	if (tk(tokens)->type & TOKEN_RED)
	{
		return (tk(tokens->next)->type & TOKEN_JOIN);
	}
	return (1);
}

/*
* I hate words neibghors unless they have companion
* */
int	check_sub_cmd(t_list *tokens)
{
	int	has_words;
	int	sub_cmd_count;

	while (tokens && !(tk(tokens)->type & TOKEN_EOL))
	{
		sub_cmd_count = 0;
		has_words = 0;
		while (tokens && !(tk(tokens)->type & (TOKEN_LIST | TOKEN_PIPE)))
		{
			if ((tk(tokens)->type & TOKEN_WORD))
				has_words = 1;
			if (tk(tokens)->type & TOKEN_SUB_CMD)
				sub_cmd_count++;
			if (tk(tokens)->type & TOKEN_RED)
				tokens = tokens->next;
			tokens = tokens->next;
		}
		if ((has_words == 1 && sub_cmd_count != 0) || sub_cmd_count > 1)
			return (0);
		if (tokens == NULL)
			break ;
		tokens = tokens->next;
	}
	return (1);
}

int	check_syntax(t_list *tokens)
{
	t_list	*head;

	head = tokens;
	if (is_special_token(tk(tokens)))
		return (0);
	if (tokens == NULL)
		return (1);
	while (tokens)
	{
		if (check_if_followed(tokens)
			|| !check_redirections(tokens)
			|| tk(tokens)->type == TOKEN_INVALID)
			return (0);
		tokens = tokens->next;
	}
	if (!check_sub_cmd(head))
		return (0);
	return (1);
}
