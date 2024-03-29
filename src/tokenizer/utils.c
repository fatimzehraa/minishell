/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:56:49 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/11 09:13:37 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include "token.h"
#include "str.h"
#include <stdlib.h>

inline t_token	*tk(t_list *node)
{
	t_token	*token;

	token = (node->content);
	return (token);
}

t_list	*new_token(char	*word)
{
	t_list	*node;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	str_mk(&token->str, word);
	token->type = TOKEN_EOL;
	token->has_space = 0;
	token->len = 0;
	node = ft_lstnew(token);
	if (node == NULL)
		free(token);
	return (node);
}

int	tk_fill(t_list *node, enum e_token type, char *dup_value, int len)
{
	tk(node)->type = type;
	tk(node)->len = len;
	if (len == -1)
	{
		tk(node)->len = ft_strlen(dup_value) + 1;
		tk(node)->type = TOKEN_INVALID;
		type = TOKEN_INVALID;
	}
	if (type & (TOKEN_LITERAL | TOKEN_TEMPLATE | TOKEN_SUB_CMD))
		tk(node)->len += 2;
	if (dup_value != NULL)
		if (!str_pnclone(&tk(node)->str, dup_value, len))
			return (0);
	return (1);
}

void	free_token(void *ptr)
{
	t_token	*tk;

	tk = (t_token *)ptr;
	free(tk->str.val);
	str_init(&tk->str);
	free(ptr);
}
