#include "list.h"
#include "minishell.h"
#include "str.h"
#include "token.h"

/*int	is_new_token(char c)
{
	int	
}*/

t_list	*ft_get_node(char *cmd)
{
	t_list	*node;

	node = new_token(NULL);
	if (ft_strncmp(cmd, ">>", 2) == 0)
	{
		tk(node)->type = TOKEN_RED_APPEND;
		tk(node)->len = 2;
	}
	if (ft_strncmp(cmd, "<<", 2) == 0)
	{
		tk(node)->type = TOKEN_HEREDOC;
		tk(node)->len = 2;
	}
	else if (*cmd == '>')
	{
		tk(node)->type = TOKEN_RED_OUT;
		tk(node)->len = 1;
	}
	else if (*cmd == '<')
	{
		tk(node)->type = TOKEN_RED_IN;
		tk(node)->len = 1;
	}
	else if (*cmd == '|')
	{
		tk(node)->type = TOKEN_PIPE;
		tk(node)->len = 1;
	}
	else if (is_space(*cmd))
	{
		tk(node)->type = TOKEN_WHITESPACE;
		tk(node)->len = 1;
	}
	else if (*cmd == '\'')
	{
		tk(node)->type = TOKEN_LITERAL;	
		tk(node)->len = string_len(cmd + 1, '\'') + 1;
		tk(node)->value = ft_strndup(cmd, tk(node)->len);
	}
	else if (*cmd == '\"')
	{
		tk(node)->type = TOKEN_TEMPLATE;
		tk(node)->len = string_len(cmd + 1, '\"') + 1;
		tk(node)->value = ft_strndup(cmd, tk(node)->len);
	}
	else if (*cmd == '$' && is_var(cmd + 1))
	{
		tk(node)->type = TOKEN_VAR;
		tk(node)->len = var_len(cmd + 1) + 1;
		tk(node)->value = ft_strndup(cmd, tk(node)->len);
	}
	else
	{
		tk(node)->type = TOKEN_WORD;
		tk(node)->len = word_len(cmd);
		tk(node)->value = ft_strndup(cmd, tk(node)->len);
	}	
	return (node);
}

t_list	*tokenizer(char	*command)
{
	t_list	*list;
	t_list	*node;

	list = NULL;
	while (*command)
	{
		node = ft_get_node(command);
// ghan3tiwha fin kaybda line o trje3 l commande w type dyalha f node
		if (node == NULL)
		{
			return (ft_lstclear(&list, free_token), NULL);
		}
		ft_lstadd_back(&list, node);
		command += tk(node)->len;
	}
	return (list);
}
