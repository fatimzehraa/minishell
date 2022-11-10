/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:09:51 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:39:58 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include "cmd.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_pid_t.h>
#include <sys/signal.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parser.h"
#include "str.h"
#include "exec.h"
#include <stdio.h>

int	check_builins(char *s)
{
	return (ft_strncmp(s, "cd", 3) == 0
		|| ft_strncmp(s, "pwd", 4) == 0
		|| ft_strncmp(s, "export", 7) == 0
		|| ft_strncmp(s, "unset", 6) == 0
		|| ft_strncmp(s, "env", 4) == 0
		|| ft_strncmp(s, "echo", 5) == 0
		|| ft_strncmp(s, "exit", 5) == 0);
}

int	execute_bultin(t_ctx *ctx, t_list *cmds, int cmd_fd[2])
{
	t_vec	cmd;
	int		fd[2];

	cmd_fd[0] = -1;
	cmd_fd[1] = -1;
	fd[0] = dup(0);
	fd[1] = dup(1);
	cmd = get_cmd(cmds)->words;
	ft_dup(cmds, cmd_fd, -1);
	if (ft_strncmp(cmd.content[0], "cd", 3) == 0)
		execute_cd(ctx, &cmd);
	else if (ft_strncmp(cmd.content[0], "pwd", 4) == 0)
		execute_pwd(ctx);
	else if (ft_strncmp(cmd.content[0], "export", 7) == 0)
		execute_export(ctx, cmd);
	else if (ft_strncmp(cmd.content[0], "unset", 6) == 0)
		execute_unset(ctx, cmd);
	else if (ft_strncmp(cmd.content[0], "env", 4) == 0)
		execute_env(ctx, cmd);
	else if (ft_strncmp(cmd.content[0], "echo", 5) == 0)
		execute_echo(&cmd);
	else if (ft_strncmp(cmd.content[0], "exit", 5) == 0)
		execute_exit(ctx, cmd);
	dup2(fd[0], 0);
	return (close(fd[0]), dup2(fd[1], 1), close(fd[1]));
}

void	ft_exec_child(t_ctx *ctx, t_list *cmds, char *cmd, int cmd_fd[])
{
	int	fd_in;

	fd_in = cmd_fd[2];
	if (cmd == NULL)
		exit(127);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_dup(cmds, cmd_fd, fd_in);
	execve(cmd, (char **)get_cmd(cmds)->words.content,
		(char **)ctx->env.content);
	ft_putstr(2, "minishell: ");
	perror(cmd);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

int	run_cmd(t_ctx *ctx, t_list *cmd, int cmd_fd[], int fd[])
{
	char		*name;
	int			pid;
	static int	last_fd = -1;

	name = get_command(ctx, cmd);
	if (is_dir(name))
		return (-1);
	cmd_fd[0] = last_fd;
	if (cmd->next != NULL)
	{
		pipe(fd);
		last_fd = fd[0];
		cmd_fd[1] = fd[1];
	}
	else
		cmd_fd[1] = -1;
	cmd_fd[2] = fd[0];
	pid = fork();
	if (pid == 0)
		ft_exec_child(ctx, cmd, name, cmd_fd);
	close(cmd_fd[0]);
	close(cmd_fd[1]);
	if (!cmd->next)
		last_fd = -1;
	return (pid);
}

int	execute(t_list *cmds, t_ctx *ctx)
{
	int		fd[2];
	int		cmd_fd[3];
	pid_t	pid;

	g_exit_status = 0;
	pid = -1;
	if (cmds && !cmds->next && get_cmd(cmds)->words.size != 0
		&& check_builins(get_cmd(cmds)->words.content[0]))
		return (execute_bultin(ctx, cmds, cmd_fd), 0);
	fd[0] = -1;
	fd[1] = -1;
	while (cmds)
	{
		pid = run_cmd(ctx, cmds, cmd_fd, fd);
		if (pid == -1)
			return (0);
		cmds = cmds->next;
	}
	ft_wait(ctx, pid);
	return (1);
}
