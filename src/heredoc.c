/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:55:29 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:55:36 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "list.h"
#include "exec.h"
#include <stdio.h>
#include <readline/readline.h>
#include "str.h"
#include "token.h"
#include <fcntl.h>
#include <unistd.h>
#include "parser.h"
#include "vector.h"

void	expand_here_var(t_ctx *ctx, int fd, char *str)
{
	int	holder;
	int	len;

	while (*str)
	{
		if (*str == '$' && is_var(str + 1))
		{
			str++;
			len = var_len(str);
			holder = search_vec(&ctx->env, str, len);
			if (holder != -1)
				ft_putstr(fd, ctx->env.content[holder] + len + 1);
		}
		else
		{
			len = until(str + 1, "$") + 1;
			write(fd, str, len);
		}
		str += len;
	}
}

void	heredoc(t_ctx *ctx, t_list *tks, int is_expandable)
{
	t_str	*delimiter;
	int		fd;
	char	*line;
	char	*file_name;

	delimiter = &tk(tks->next)->str;
	file_name = get_tmp();
	fd = open(file_name, O_CREAT | O_WRONLY, 0666);
	if (fd == -1)
		return ;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || str_psame(delimiter, line, ft_strlen(line) + 1))
			break ;
		if (is_expandable)
			expand_here_var(ctx, fd, line);
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	str_free(&tk(tks->next)->str);
	str_mk(&tk(tks->next)->str, file_name);
}

void	read_heredocs(t_ctx *ctx, t_list *tokens)
{
	while (tokens)
	{
		if (tk(tokens)->type == TOKEN_HEREDOC)
			heredoc(ctx, tokens, join_here(tokens));
		tokens = tokens->next;
	}
}
