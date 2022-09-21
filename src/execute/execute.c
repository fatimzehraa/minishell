#include "list.h"
#include "minishell.h"
#include "cmd.h"
#include <signal.h>
#include <sys/_types/_pid_t.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
int execute(t_list *cmds, t_ctx *ctx)
{
	t_cmd	*cmd;
	char	*path;
	int		i;

	cmd = get_cmd(cmds);
	i = search_vec_(&ctx->env, "PATH");
	path = ctx->env.content[i] + 5;
//	printf("pathhh: %s\n", path);
	path = "/bin/ls";
	pid_t		pid = fork();
	if (pid == 0)
	{
		execve(path, (char **)cmd->words.content, (char **)ctx->env.content);
	}
	wait(NULL);
//	execvp("ls", (char **)cmd->words.content);
	printf("nnnn\n");
	return 0;
}
