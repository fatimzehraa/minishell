#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <term.h>
#include "token.h"
#include "vector.h"

int	exit_status = 0;

int	launch(t_ctx *ctx)
{
	char	*line;

	while (1)
	{
		line = readline("$> ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] != '\0')
			add_history(line);
		exec_line(line, ctx);
		free(line);
	}
	return (1);
}

void	setup_readline(void)
{
	rl_instream = stdin;
	rl_outstream = stderr;
}

void	setup_termios(t_ctx *ctx)
{
	struct termios	term;
	struct termios	restore;

	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	ctx->restore = restore;
}

int	main(int argc, char *argv[], char **envp)
{
	t_ctx	ctx;

	(void)argc;
	(void)argv;
	setup_readline();
	setup_termios(&ctx);
	setup_signals(&ctx);
	if (!clone_env(envp, &ctx.env))
		return (1);
	launch(&ctx);
	return (0);
}
