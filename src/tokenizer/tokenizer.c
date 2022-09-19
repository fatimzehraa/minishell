#include "list.h"
#include "minishell.h"
#include "str.h"
#include "token.h"

char *mark_space(t_list *node, char *line)
{
	if (is_space(*line))
	{
		while (is_space(*line))
			line++;
		tk(node)->has_space = 1;
	}
	else
		tk(node)->has_space = 0;
	return line;
}

int get_simple_nodes(t_list *node, char *line)
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
		return 0;
	while (is_space(line[tk(node)->has_space]))
		tk(node)->has_space++;
	return 1;
}

char *ft_get_node(t_list	*node, char *line)
{
	if (get_simple_nodes(node, line))
		return line + tk(node)->has_space;
	else if (*line == CHAR_SQ)
	{
		tk_fill(node, TOKEN_WORD, line + 1, string_len(line + 1, CHAR_SQ));
		line += 2;
	}
	else if (*line == CHAR_DQ)
	{
		tk_fill(node, TOKEN_TEMPLATE, line + 1, string_len(line + 1, CHAR_DQ));
		line += 2;
	}
	else if (*line == '$' && is_var(line + 1))
	{
		line++;
		tk_fill(node, TOKEN_VAR, line, var_len(line));
	}
	else
		tk_fill(node, TOKEN_WORD, line, word_len(line));
	if (tk(node)->str.val == NULL)
		return NULL;
	line += tk(node)->str.size;
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
		if (node == NULL)
			return (ft_lstclear(&list, free_token), NULL);
		line = ft_get_node(node, line);
		if (line == NULL)
			return (ft_lstclear(&list, free_token), NULL);
		ft_lstadd_back(&list, node);
	}
	node = new_token(NULL);
	if (node == NULL)
		return (ft_lstclear(&list, free_token), NULL);
	ft_lstadd_back(&list, node);
	return (list);
}
