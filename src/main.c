#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "token.h"

int	launch()
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
		exec_line(line);
		free(line);
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
