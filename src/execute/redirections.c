/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:34:13 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:58:00 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include "str.h"
#include "token.h"
#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

void	red_out(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[1]);
	fd = open(tk(reds->next)->str.val, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("minishell");
		return ;
	}
	cmd_fd[1] = fd;
}

// test : ls > filewithnoperm | wc
void	red_in(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[0]);
	fd = open(tk(reds->next)->str.val, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return ;
	}
	cmd_fd[0] = fd;
}

void	red_here(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[0]);
	fd = open(tk(reds->next)->str.val, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return ;
	}
	unlink(tk(reds->next)->str.val);
	cmd_fd[0] = fd;
}

void	red_append(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[1]);
	fd = open(tk(reds->next)->str.val, O_APPEND | O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("minishell");
		return ;
	}
	cmd_fd[1] = fd;
}

void	redirect(t_list *reds, int cmd_fd[])
{
	int	fd;

	fd = 0;
	while (reds)
	{
		if (tk(reds)->type == TOKEN_RED_OUT)
			red_out(reds, cmd_fd, fd);
		else if (tk(reds)->type == TOKEN_RED_IN)
			red_in(reds, cmd_fd, fd);
		else if (tk(reds)->type == TOKEN_HEREDOC)
			red_here(reds, cmd_fd, fd);
		else if (tk(reds)->type == TOKEN_RED_APPEND)
			red_append(reds, cmd_fd, fd);
		reds = reds->next;
	}
}
