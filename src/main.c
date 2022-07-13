#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int	launch()
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
		printf("%s\n", command);
	}
	return (1);
}

int main (int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	setup_signals();
	launch();
	return 0;
}
