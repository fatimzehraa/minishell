#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include "list.h"
#include "str.h"
#include "token.h"
#include "parser.h"
#include "minishell.h"
#include "exec.h"

void	exec_line(char *line, t_ctx *ctx)
{
	t_list	*tokens;
	t_list	*cmds;

	tokens = tokenizer(line);
	//if (check_syntax(tokens)) continue
	if (!check_syntax(tokens))
	{
		printf("syntax error\n");
		return ;
	}
	read_heredocs(tokens);
	// handel logic .. && ||
	cmds = parser(tokens, ctx);
	//while (tokens)
	//{
	//	printf("%s\t |%d|\n", tk(tokens)->str.val, tk(tokens)->has_space);
	//	tokens = tokens->next;
	//}
	switch_handler(ctx);
	execute(cmds, ctx);
	switch_handler(ctx);
}
