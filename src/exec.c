#include <stdio.h>
#include "list.h"
#include "str.h"
#include "token.h"
#include "minishell.h"

void	exec_line(char *cmd, t_ctx *ctx)
{
	t_list	*tokens;

	(void) ctx;
	tokens = tokenizer(cmd);
	//if (check_syntax(tokens)) continue
	//t_list command parser(tokens)
	//void execute(command)
	while (tokens)
	{
		printf("content: %s\n    type: %d\n", tk(tokens)->value, tk(tokens)->type);
		tokens = tokens->next;
	}
}
