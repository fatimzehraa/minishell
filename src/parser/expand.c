/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:57:33 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/12 13:43:07 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "str.h"
#include "token.h"
#include "parser.h"
#include <stdlib.h>
#include "minishell.h"
#include "utils.h"
#include "parser.h"

/*
 * ft_lstadd_back has an extra protection
 * if we try list and new point to the same list
 * it will just ignore them and do nothing
 * not a good idea thought (but norm)
*/
int	expand_var(t_ctx *ctx, t_list *token)
{
	t_list	*next;
	char	*value;
	t_list	*node;
	int		has_space;

	value = get_env(tk(token)->str.val, &ctx->env);
	if (*value == '\0')
		return (str_free(&tk(token)->str), 1);
	has_space = tk(token)->has_space;
	next = token->next;
	token->next = NULL;
	free(tk(token)->str.val);
	node = token;
	while (*value && node != NULL)
	{
		str_init(&tk(node)->str);
		if (get_next_word(&tk(node)->str, &value) == 0)
			return (ft_lstadd_back(&token, next), 0);
		add(node, &token, 0);
		if (*value)
			node = new_token(NULL);
	}
	if (node == NULL)
		tk(node)->has_space = has_space;
	return (ft_lstadd_back(&token, next), node != NULL);
}

t_list	*del_astrisk(t_list *curr, t_list *next)
{
	t_list	*tmp;

	while (curr && curr != next)
	{
		tmp = curr->next;
		ft_lstdelone(curr, free_token);
		curr = tmp;
	}
	return (next);
}

t_list	*_expand_asterisk(t_list *curr, t_list *begin)
{
	t_list	*res;
	t_list	*next;

	next = curr;
	while (tk(next)->type & (TOKEN_ASTERISK | TOKEN_WORD)
		&& tk(next)->has_space == 0)
		next = next->next;
	next = next->next;
	res = match(begin->next);
	if (res)
	{
		begin->next = res;
		ft_lstadd_back(&res, next);
	}
	else
	{
		while (curr != next)
		{
			if (tk(curr)->type == TOKEN_ASTERISK)
				tk(curr)->type = TOKEN_WORD;
			curr = curr->next;
		}
	}
	return (del_astrisk(curr, next));
}

/*
 * 1. search for *
 * 2. get end of expression
 * 3. match
 * 4. link
 */
int	expand_asterisk(t_list *tks)
{
	t_list	*curr;
	t_list	*head;

	curr = tks;
	head = tks;
	while (curr)
	{
		if (tk(curr)->type == TOKEN_ASTERISK)
			curr = _expand_asterisk(curr, head);
		if (curr == NULL)
			break ;
		if (tk(curr)->has_space)
			head = curr;
		curr = curr->next;
	}
	return (1);
}

int	expand(t_list *tokens, t_ctx *ctx)
{
	t_list	*curr;

	curr = tokens;
	while (curr)
	{
		if (tk(curr)->type == TOKEN_LITERAL)
			tk(curr)->type = TOKEN_WORD;
		else if (tk(curr)->type == TOKEN_VAR)
		{
			if (expand_var(ctx, curr) == 0)
				return (ft_lstclear(&tokens, free_token), 0);
		}
		else if (tk(curr)->type == TOKEN_LITERAL)
			tk(curr)->type = TOKEN_WORD;
		else if (tk(curr)->type == TOKEN_TEMPLATE)
			if (expand_template(curr, ctx) == 0)
				return (ft_lstclear(&tokens, free_token), 0);
		curr = curr->next;
	}
	return (expand_asterisk(tokens));
}
