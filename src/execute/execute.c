#include "list.h"
#include "minishell.h"
#include "cmd.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_pid_t.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"
#include "str.h"

#include <stdio.h>

char	*find_path(char *path, char *cmd)
{
	int		size;
	char	*cmd_path;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	while(path)
	{
		size = until(path, ":");
		cmd_path = malloc(size + cmd_len + 2);
		strncpy(cmd_path, path, size);
		strncpy(cmd_path, "/", 1);
		strncpy(cmd_path, cmd, cmd_len);
		cmd_path[size + cmd_len + 2] = 0;
		if (access(cmd_path, F_OK))
			return (cmd_path);
		path += size;
	}
	return NULL;
}

int	execute_cmd(t_cmd *cmd, char *path, t_ctx *ctx)
{
	char	*command;
	int		cmd_len;
	char	*cmd_path;

	command = cmd->words.content[0];
	cmd_len = ft_strlen(command);
	if (command[0] == '\\')
		cmd_path = command;
	else
	{
		cmd_path = find_path(path, command);
	}
	execve(path, (char **)cmd->words.content, (char **)ctx->env.content);
	return (1);
}

int execute(t_list *cmds, t_ctx *ctx)
{
	t_cmd	*cmd;
	char	*path;
	int		i;

	cmd = get_cmd(cmds);
	i = search_vec_(&ctx->env, "PATH");
	path = ctx->env.content[i] + 5;
	path = "/bin/ls";
	pid_t		pid = fork();
	if (pid == 0)
	{
		execute_cmd(cmd, path, ctx);
	}
	wait(NULL);
	return 0;
}
