/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:06:51 by fael-bou          #+#    #+#             */
/*   Updated: 2022/10/05 13:47:58 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "exec.h"

#include <stdio.h>

char	*find_path(char *path, char *cmd)
{
	int		size;
	char	*cmd_path;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	if (cmd[0] == '\\')
		return (cmd);
	while(*path)
	{
		size = until(path, ":");
		cmd_path = malloc(size + cmd_len + 2);
		ft_strncpy(cmd_path, path, size);
		ft_strncpy(cmd_path + size, "/", 1);
		ft_strncpy(cmd_path + size + 1, cmd, cmd_len);
		cmd_path[size + cmd_len + 2] = 0;
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
		path += size + 1;
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
	index = search_vec_(&ctx->env, "PATH");
	path = ctx->env.content[index] + 5;
	command = cmd->words.content[0];
	cmd_path = find_path(path, command);
	// TODO: if PATH == NULL || not found in PATH
	return cmd_path;
}

void ft_exec_child(t_ctx *ctx, t_list *cmds, char *cmd, int cmd_fd[], int fd_in)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(cmd_fd[0], 0);
	close(cmd_fd[0]);
	dup2(cmd_fd[1], 1);
	close(cmd_fd[1]);
	close(fd_in);
	execve(cmd, (char **)get_cmd(cmds)->words.content, (char **)ctx->env.content);
}

int ft_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	while (4)
	{
		if (waitpid(-1, &status, 0) == -1)
			break;
	}
	return (status);
}

int	execute_bultin(t_list *cmds)
{
	t_vec	cmd;

	cmd = get_cmd(cmds)->words;
	if (ft_strncmp(cmd.content[0], "cd", 3) == 0)
	{
		execute_cd(cmd);
		return (1);
	}
	/*
	else if (ft_strncmp(cmd->words.content[0], "pwd", 4) == 0)
		execute_pwd(cmd);
	else if (ft_strncmp(cmd->words.content[0], "export", 7) == 0)
		execute_export(cmd);
	else if (ft_strncmp(cmd->words.content[0], "unset", 6) == 0)
		execute_unset(cmd);
	else if (ft_strncmp(cmd.content[0], "env", 4) == 0)
		execute_env(cmd);
	else*/ 
	if (ft_strncmp(cmd.content[0], "exit", 5) == 0)
		exit(1);
	else
		return (0);
}

int execute(t_list *cmds, t_ctx *ctx)
{
	int		fd[2];
	int		cmd_fd[2];
	int		last_fd;
	pid_t	pid;
	char	*cmd;

	if (cmds && !cmds->next && execute_bultin(cmds))
		return (0);
	last_fd = -1;
	while (cmds)
	{
		cmd = get_command(ctx, cmds);
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
		close(fd[1]);
		cmds = cmds->next;
	}
	ft_wait(pid);
	return 0;
}

