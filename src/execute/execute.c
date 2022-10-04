/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:06:51 by fael-bou          #+#    #+#             */
/*   Updated: 2022/10/04 14:44:54 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include "cmd.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/_types/_pid_t.h>
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
 
int	execute_cmd(t_cmd *cmd, char *cmd_path, t_ctx *ctx, int fd[], int fd_in)
{
	pid_t		pid = fork();

	if (pid == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd_in);
		execve(cmd_path, (char **)cmd->words.content, (char **)ctx->env.content);
	}
	return (1);
}

int execute(t_list *cmds, t_ctx *ctx)
{
	t_cmd	*cmd;
	char	*path;
	int		i;
	int		fd[2];
	int		cmd_fd[2];
	char	*command;
	char	*cmd_path;
	int		last_fd;

	last_fd = -1;
	while (cmds)
	{
		cmd = get_cmd(cmds);
		i = search_vec_(&ctx->env, "PATH");
		path = ctx->env.content[i] + 5;
		cmd_fd[0] = last_fd;
		if (cmds->next != NULL)
		{
			pipe(fd);
			last_fd = fd[0];
			cmd_fd[1] = fd[1];
		}
		else
			cmd_fd[1] = -1;
		command = cmd->words.content[0];
		cmd_path = find_path(path, command);
		execute_cmd(cmd, cmd_path, ctx, cmd_fd, fd[0]);
		close(fd[1]);
		cmds = cmds->next;
	}
	while (4)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break;
	}
	return 0;
}

