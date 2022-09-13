#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "token.h"
#include "vector.h"

int	launch(t_ctx *ctx)
{
	char *command;

	while (1)
	{
		command = readline("$> ");
		if (command == NULL)
		{
			printf("exit\n");
			break;
		}
		if (command[0] != '\0')
			add_history(command);
		exec_line(command, ctx);
		free(command);
	}
	return (1);
}

int main (int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	t_ctx	ctx;

	setup_signals();
	if(!clone_env(envp, &ctx.env))
		return (1);
	launch(&ctx);
	return 0;
}
