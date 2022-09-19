#include <stdio.h>
#include "list.h"
#include "str.h"
#include "token.h"
#include "parser.h"
#include "minishell.h"

void	exec_line(char *line, t_ctx *ctx)
{
	t_list	*tokens;

	(void) ctx;
	tokens = tokenizer(line);
	//if (check_syntax(tokens)) continue
	parser(tokens, ctx);
	//t_list command parser(tokens)
	//void execute(command)
	while (tokens)
	{
		printf("%s\t |%d|\n", tk(tokens)->str.val, tk(tokens)->has_space);
		tokens = tokens->next;
	}
}
