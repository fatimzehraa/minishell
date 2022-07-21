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
	if (word)
		token->len = ft_strlen(word);
	else
		token->len = - 1;
	node = ft_lstnew(token);
	if (node == NULL)
		free(token);
	return(node);
}

void	free_token(void *ptr)
{
	t_list	*node;
	
	node = (t_list *)ptr;
	free(tk(node)->value);
	free(node->content);
	free(node);
}
