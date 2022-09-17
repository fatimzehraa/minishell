#include <stdio.h>
#include "list.h"
#include "str.h"
#include "token.h"
void	exec_line(char *cmd)
{
	t_list	*tokens;

	tokens = tokenizer(cmd);
	//if (check_syntax(tokens)) continue
	//t_list command parser(tokens)
	//void execute(command)
	while (tokens)
	{
		printf("%s\t |%d|\n", tk(tokens)->value, tk(tokens)->type);
		tokens = tokens->next;
	}
}
