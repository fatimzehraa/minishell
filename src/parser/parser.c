#include "list.h"
#include "parser.h"
#include "minishell.h"
#include "cmd.h"
#include "str.h"
#include "token.h"
#include "vector.h"

t_list *mk_cmd()
{
	t_list	*node;
	t_cmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->red = NULL;
	init_vec(cmd->words, 20);
	node = ft_lstnew(cmd);
	if (node == NULL)
		free(cmd);
	return(node);
}

t_cmd *get_cmd(t_list *node)
{
	return ((t_cmd *) node->content);
}


t_list * filter_cmd(t_list *tks)
{
	t_list *head;
	t_list *cur;
	t_list *cmd;

	head = NULL;
	cur = tks;
	while (cur)
	{
		cmd = mk_cmd();
		while (tk(cur)->type & (TOKEN_EOL | TOKEN_PIPE))
		{
			if (tk(cur)->type & TOKEN_RED)
			{
				ft_lstadd_back(&(get_cmd(cmd)->red), cur);
				ft_lstadd_back(&(get_cmd(cmd)->red), cur->next);
				cur = cur->next->next;
				continue;
			}
			vec_add(get_cmd(cmd)->words, tk(cur)->str.val);
			str_init(&tk(cur)->str);
			cur = delete_cur(cur, free_token);
		}
		ft_lstadd_back(&head, cmd);
		cur = delete_cur(cur, free_token);
	}

	return head;
}

t_list	*parser(t_list *tokens, t_ctx *ctx)
{

	expand(tokens, ctx);
	join(tokens);
	tokens = filter_cmd(tokens);
	return (tokens);
}
