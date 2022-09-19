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
	init_vec(&cmd->words, 20);
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
		while ((tk(cur)->type & (TOKEN_EOL | TOKEN_PIPE)) == 0)
		{
			if (tk(cur)->type & TOKEN_RED)
			{
				t_list *next = cur->next->next;
				cur->next->next = NULL;
				ft_lstadd_back(&(get_cmd(cmd)->red), cur);
				cur = next;
				continue;
			}
			vec_add(&get_cmd(cmd)->words, tk(cur)->str.val);
			str_init(&tk(cur)->str);
			cur = delete_cur(cur, free_token);
		}
		ft_lstadd_back(&head, cmd);
		cur = delete_cur(cur, free_token);
	}

	return head;
}

#include <stdio.h>
t_list	*parser(t_list *tokens, t_ctx *ctx)
{

	expand(tokens, ctx);
	join(tokens);
	tokens = filter_cmd(tokens);
	t_list *cur;
	
	cur = tokens;
	while (cur) {
		t_cmd *cmd = get_cmd(cur);
		printf("words:\n");
		int i = 0;
		while (i < cmd->words.size) {
			printf("%s ", (char *) cmd->words.content[i]);
			i++;
		}
		printf("\n");
		t_list *reds = cmd->red;
		while (reds)
		{
			printf("%s\t |%d|\n", tk(reds)->str.val, tk(reds)->has_space);
			reds = reds->next;
		}
		
		cur = cur->next;
	}
	return (tokens);
}
