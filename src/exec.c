#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
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
	if (tokens == NULL)
		return ;
	//if (check_syntax(tokens)) continue
	parser(tokens, ctx);
	//execute(tokens);
	//while (tokens)
	//{
	//	printf("%s\t |%d|\n", tk(tokens)->str.val, tk(tokens)->has_space);
	//	tokens = tokens->next;
	//}
	
	switch_handler(ctx);
	sleep(5);
	// after exec
	switch_handler(ctx);
}
