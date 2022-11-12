/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:34:13 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/12 12:27:22 by fatimzehra       ###   ########.fr       */
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

int	red_out(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[1]);
	fd = open(tk(reds->next)->str.val, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("minishell");
		return (0);
	}
	cmd_fd[1] = fd;
	return (1);
}

// test : ls > filewithnoperm | wc
int	red_in(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[0]);
	fd = open(tk(reds->next)->str.val, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(2, "minishell: ");
		perror(tk(reds->next)->str.val);
		return (0);
	}
	cmd_fd[0] = fd;
	return (1);
}

int	red_here(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[0]);
	fd = open(tk(reds->next)->str.val, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(2, "minishell: ");
		perror(tk(reds->next)->str.val);
		return (0);
	}
	unlink(tk(reds->next)->str.val);
	cmd_fd[0] = fd;
	return (1);
}

int	red_append(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[1]);
	fd = open(tk(reds->next)->str.val, O_APPEND | O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr(2, "minishell: ");
		perror(tk(reds->next)->str.val);
		return (0);
	}
	cmd_fd[1] = fd;
	return (1);
}

int	redirect(t_list *reds, int cmd_fd[])
{
	int	fd;
	int	result;

	fd = 0;
	result = 1;
	while (result && reds)
	{
		if (tk(reds)->type == TOKEN_RED_OUT)
			result = red_out(reds, cmd_fd, fd);
		else if (tk(reds)->type == TOKEN_RED_IN)
			result = red_in(reds, cmd_fd, fd);
		else if (tk(reds)->type == TOKEN_HEREDOC)
			result = red_here(reds, cmd_fd, fd);
		else if (tk(reds)->type == TOKEN_RED_APPEND)
			result = red_append(reds, cmd_fd, fd);
		reds = reds->next;
	}
	return (result);
}
