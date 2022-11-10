/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:15:16 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 15:15:18 by fael-bou         ###   ########.fr       */
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
			|| tk(tokens->next)->type == TOKEN_EOL));
}

int	check_redirections(t_list *tokens)
{
	if (tk(tokens)->type & TOKEN_RED)
	{
		if (tk(tokens->next)->type & TOKEN_JOIN)
			return (1);
		else
			return (0);
	}
	return (1);
}

int	check_syntax(t_list *tokens)
{
	if (is_special_token(tk(tokens)))
		return (0);
	if (tk(tokens)->type == TOKEN_EOL)
		return (1);
	while (tk(tokens)->type != TOKEN_EOL)
	{
		if (check_if_followed(tokens)
			|| !check_redirections(tokens)
			|| tk(tokens)->type == TOKEN_INVALID)
			return (0);
	tokens = tokens->next;
	}
	return (1);
}
