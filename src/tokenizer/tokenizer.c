/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:56:44 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/11 13:25:20 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include "str.h"
#include "token.h"

char	*mark_space(t_list *node, char *line)
{
	if (is_space(*line) || *line == '\0')
	{
		while (is_space(*line))
			line++;
		tk(node)->has_space = 1;
	}
	else
		tk(node)->has_space = 0;
	return (line);
}

int	get_simple_nodes(t_list *node, char *line)
{
	if (ft_strncmp(line, ">>", 2) == 0)
		tk_fill(node, TOKEN_RED_APPEND, NULL, 2);
	else if (ft_strncmp(line, "<<", 2) == 0)
		tk_fill(node, TOKEN_HEREDOC, NULL, 2);
	else if (ft_strncmp(line, "&&", 2) == 0)
		tk_fill(node, TOKEN_AND, NULL, 2);
	else if (ft_strncmp(line, "||", 2) == 0)
		tk_fill(node, TOKEN_OR, NULL, 2);
	else if (*line == '>')
		tk_fill(node, TOKEN_RED_OUT, NULL, 1);
	else if (*line == '<')
		tk_fill(node, TOKEN_RED_IN, NULL, 1);
	else if (*line == '|')
		tk_fill(node, TOKEN_PIPE, NULL, 1);
	else
		return (0);
	return (1);
}

int	sub_len(char *s)
{
	int	count;
	int	len;

	count = 1;
	len = 0;
	s++;
	while (is_space(s[len]))
		len++;
	if (s[len] == ')')
		return (-1);
	while (count > 0 && s[len])
	{
		if (s[len] == '(')
			count++;
		if (s[len] != CHAR_DQ && s[len] != CHAR_SQ && s[len + 1] == ')')
			count--;
		len++;
	}
	if (s[len] == '\0')
		return (-1);
	return (len);
}

char	*ft_get_node(t_list	*node, char *line)
{
	if (node == NULL)
		return (NULL);
	if (get_simple_nodes(node, line))
		return (mark_space(node, line + tk(node)->len));
	else if (*line == CHAR_SQ)
		tk_fill(node, TOKEN_LITERAL, line + 1, string_len(line + 1, CHAR_SQ));
	else if (*line == CHAR_DQ)
		tk_fill(node, TOKEN_TEMPLATE, line + 1, string_len(line + 1, CHAR_DQ));
	else if (*line == '(')
		tk_fill(node, TOKEN_SUB_CMD, line + 1, sub_len(line));
	else if (*line == '$' && is_var(line + 1))
	{
		line++;
		tk_fill(node, TOKEN_VAR, line, var_len(line));
	}
	else if (*line == '*')
		tk_fill(node, TOKEN_ASTERISK, line, 1);
	else
		tk_fill(node, TOKEN_WORD, line, word_len(line));
	if (tk(node)->str.val == NULL)
		return (NULL);
	line += tk(node)->len;
	line = mark_space(node, line);
	return (line);
}

t_list	*tokenizer(char	*line)
{
	t_list	*list;
	t_list	*node;

	list = NULL;
	while (*line)
	{
		node = new_token(NULL);
		line = ft_get_node(node, line);
		if (line == NULL)
			return (ft_lstclear(&list, free_token), NULL);
		ft_lstadd_back(&list, node);
	}
	return (list);
}
