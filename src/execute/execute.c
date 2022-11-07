#include "list.h"
#include "minishell.h"
#include "cmd.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/signal.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"
#include "str.h"
#include "exec.h"
#include <sys/stat.h>

#include <stdio.h>

int	is_dir(char *filename, char *orginal)
{
	struct stat	st;

	(void)orginal;
	errno = 0;
	stat(filename, &st);
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr(2, "minishell: ");
		ft_putstr(2, filename);
		ft_putstr(2, ": ");
		ft_putstr(2, strerror(EISDIR));
		ft_putstr(2, "\n");
		return (1);
	}
	return (0);
}


char	*find_path(char *path, char *cmd)
{
	int		size;
	char	*cmd_path;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	while(*path)
	{
		size = until(path, ":");
		cmd_path = malloc(size + cmd_len + 2);
		ft_strncpy(cmd_path, path, size);
		ft_strncpy(cmd_path + size, "/", 1);
		ft_strncpy(cmd_path + size + 1, cmd, cmd_len);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
		path += size + (path[size] == ':');
	}
	return NULL;
}
 
char *get_command(t_ctx *ctx, t_list *cmds)
{
	t_cmd	*cmd;
	char	*path;
	int		index;
	char	*command;
	char	*cmd_path;

	cmd = get_cmd(cmds);
	/*
	int i = 0;
	while(cmd->words.content[i])
	{
		printf("content n %d", i);
		printf("cmd->word.content = %s\n", (char *)cmd->words.content[i]);
		i++;
	}*/
	if (cmd->words.size == 0)
		return (NULL);
	/*
	if (ft_strncmp(cmd->words.content[0], "", -1) == 0)
	{
		printf("bug\n");
		return NULL;
	}*/
	index = search_vec_(&ctx->env, "PATH");
	path = ctx->env.content[index] + 5;
	command = cmd->words.content[0];
	cmd_path = find_path(path, command);
	// TODO: if PATH == NULL || not found in PATH
	if (cmd_path == NULL)
	{
		ft_putstr(2, "minishell: ");
		ft_putstr(2, cmd->words.content[0]);
		ft_putstr(2, " command not found\n");
	}
	return cmd_path;
}
int ft_wait(t_ctx *ctx, pid_t pid)
{
	int	status;

	(void)ctx;
	waitpid(pid, &status, 0);
	if (pid == - 1)
		status = 0;
	exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("^\\Quit: 3\n");
		exit_status = WTERMSIG(status) + 128;
	}
	while (4)
	{
		if (waitpid(-1, &status, 0) == -1)
			break;
	}
	return (status);
}

int	execute_bultin(t_ctx *ctx, t_list *cmds)
{
	t_vec	cmd;

	cmd = get_cmd(cmds)->words;
	if (cmd.size == 0)
		return (0);
	if (ft_strncmp(cmd.content[0], "cd", 3) == 0)
		return (execute_cd(ctx, &cmd), 1);
	else if (ft_strncmp(cmd.content[0], "pwd", 4) == 0)
		return (execute_pwd(ctx), 1);
	else if (ft_strncmp(cmd.content[0], "export", 7) == 0)
		return (execute_export(ctx, cmd), 1);
	else if (ft_strncmp(cmd.content[0], "unset", 6) == 0)
		return (execute_unset(ctx, cmd), 1);
	else if (ft_strncmp(cmd.content[0], "env", 4) == 0)
		return (execute_env(ctx, cmd), 1);
	else if (ft_strncmp(cmd.content[0], "echo", 5) == 0)
		return (execute_echo(&cmd), 1);
	else if (ft_strncmp(cmd.content[0], "exit", 5) == 0)
		return (execute_exit(ctx, cmd), 1);
	else
		return (0);
}

void ft_exec_child(t_ctx *ctx, t_list *cmds, char *cmd, int cmd_fd[], int fd_in)
{
	if (cmd == NULL)
		exit(127);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirect(get_cmd(cmds)->red, cmd_fd);
	dup2(cmd_fd[0], 0);
	close(cmd_fd[0]);
	dup2(cmd_fd[1], 1);
	close(cmd_fd[1]);
	close(fd_in);
	execve(cmd, (char **)get_cmd(cmds)->words.content, (char **)ctx->env.content);
	perror("minishell: ");
	if (errno == EACCES)
		exit(126);
	exit(127);
}

int execute(t_list *cmds, t_ctx *ctx)
{
	int		fd[2];
	int		cmd_fd[2];
	int		last_fd;
	pid_t	pid;
	char	*cmd;

	exit_status = 0;
	pid = -1;
	if (cmds && !cmds->next && execute_bultin(ctx, cmds))
		return (0);
	last_fd = -1;
	fd[0] = -1;
	fd[1] = -1;
	while (cmds)
	{
		cmd = get_command(ctx, cmds);
		if (is_dir(cmd, "hello"))
			return 0;
		cmd_fd[0] = last_fd;
		if (cmds->next != NULL)
		{
			pipe(fd);
			last_fd = fd[0];
			cmd_fd[1] = fd[1];
		}
		else
			cmd_fd[1] = -1;
		pid  = fork();
		if (pid == 0)
			ft_exec_child(ctx, cmds, cmd, cmd_fd, fd[0]);
		close(cmd_fd[0]);
		close(cmd_fd[1]);
		cmds = cmds->next;
	}
	ft_wait(ctx, pid);
//	printf("exit status :%d\n", exit_status);
	return 0;
}
