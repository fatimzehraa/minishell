/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:32:32 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 17:19:12 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include "str.h"
#include "exec.h"
#include <stdio.h>
#include "parser.h"
#include <sys/errno.h>
#include <string.h>
#include <sys/stat.h>

char	*find_path(char *path, char *cmd)
{
	int		size;
	char	*cmd_path;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	if (cmd[0] == '\0')
		return (NULL);
	while (*path)
	{
		size = until(path, ":");
		cmd_path = malloc(size + cmd_len + 2);
		if (cmd_path == NULL)
			return (NULL);
		ft_strncpy(cmd_path, path, size);
		ft_strncpy(cmd_path + size, "/", 1);
		ft_strncpy(cmd_path + size + 1, cmd, cmd_len);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
		path += size + (path[size] == ':');
	}
	return (NULL);
}

char	*get_command(t_ctx *ctx, t_list *cmds)
{
	t_cmd	*cmd;
	char	*path;
	int		index;
	char	*command;
	char	*cmd_path;

	cmd = get_cmd(cmds);
	if (cmd->words.size == 0)
		return (NULL);
	index = search_vec_(&ctx->env, "PATH");
	if (index == -1)
		return (cmd->words.content[0]);
	path = ctx->env.content[index] + 5;
	command = cmd->words.content[0];
	cmd_path = find_path(path, command);
	if (cmd_path == NULL)
	{
		ft_putstr(2, "minishell: ");
		ft_putstr(2, cmd->words.content[0]);
		ft_putstr(2, " command not found\n");
	}
	return (cmd_path);
}

int	ft_wait(t_ctx *ctx, pid_t pid)
{
	int	status;

	(void)ctx;
	waitpid(pid, &status, 0);
	if (pid == -1)
		status = 0;
	g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("^\\Quit: 3\n");
		g_exit_status = WTERMSIG(status) + 128;
	}
	while (4)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
	}
	return (status);
}

void	ft_dup(t_list *cmds, int cmd_fd[], int fd_in)
{
	redirect(get_cmd(cmds)->red, cmd_fd);
	dup2(cmd_fd[0], 0);
	close(cmd_fd[0]);
	dup2(cmd_fd[1], 1);
	close(cmd_fd[1]);
	close(fd_in);
}

int	is_dir(char *filename)
{
	struct stat	st;

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
