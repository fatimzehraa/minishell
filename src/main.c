#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "token.h"
#include "vector.h"

int exit_status = 0;

int	launch(t_ctx *ctx)
{
	char *line;

	while (1)
	{
		line = readline("$> ");
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (line[0] != '\0')
			add_history(line);
		exec_line(line, ctx);
		free(line);
	}
	return (1);
}

int main (int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	t_ctx	ctx;

	setup_signals(&ctx);
	if(!clone_env(envp, &ctx.env))
		return (1);
	launch(&ctx);
	return 0;
}
