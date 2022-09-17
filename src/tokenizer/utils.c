#include "list.h"
#include "minishell.h"
#include "token.h"
#include "str.h"
#include <stdlib.h>

t_token	*tk(t_list *node)
{
	t_token *token;

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
	token->value = word;
	token->type = TOKEN_EOL;
	if (word)
		token->len = ft_strlen(word);
	else
		token->len = - 1;
	node = ft_lstnew(token);
	if (node == NULL)
		free(token);
	return(node);
}

int tk_fill(t_list *node, enum e_token type, char *dup_value, int len)
{
	tk(node)->type = type;	
	tk(node)->len = len;
	if (dup_value != NULL)
		tk(node)->value = ft_strndup(dup_value, len);
	return tk(node)->value != NULL;
}

void	free_token(void *ptr)
{
	t_list	*node;
	
	node = (t_list *)ptr;
	free(tk(node)->value);
	free(node->content);
	free(node);
}
