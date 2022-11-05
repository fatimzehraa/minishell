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

#define FT_TMPFILE "/tmp/minishell-aaaaaa"

void	get_next_comb(char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 1;
	while (i < 7 && s[len - i] == '9')
		s[len - i++] = 'a';
	if ((s[len - i] >= 'a' && s[len - i] < 'z')
		|| (s[len - i] >= '0' && s[len - i] < '9'))
		s[len - i]++;
	else if (s[len - i] == 'z')
		s[len - i] = '0';
}

char	*get_tmp(void)
{
	char	*file;

	file = ft_strndup(FT_TMPFILE, -1);
	if (file == NULL)
		return (NULL);
	while (1)
	{
		if (access(file, F_OK | W_OK | R_OK) == 0)
		{
			get_next_comb(file);
			continue ;
		}
		break ;
	}
	return (file);
}

void expand_here_var(t_ctx *ctx, int fd, char *str)
{
	int holder;
	int len;

	while (*str) {
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

t_list *detach_tks(t_list *tks)
{
	t_list *head;
	t_list *detach;
	t_list *next;

	head = tks;
	detach = NULL;
	tks = tks->next;
	while (tks)
	{
		next = tks->next;
		tks->next = NULL;
		ft_lstadd_back(&detach, tks);
		if ((tk(tks)->type & TOKEN_JOIN) == 0)
			break;
		if (tk(tks)->has_space)
		{
			tks = next;
			break;
		}
		tks = next;
	}
	head->next = tks;
	return detach;
}

void attach(t_list *lst, t_list *node)
{
	t_list	*next;

	next = lst->next;
	lst->next = node;
	ft_lstadd_back(&node, next);
}

int join_here(t_list *tks)
{
	t_list	*detach;
	t_list	*cur;
	int		is_expandable;

	is_expandable = 1;
	detach = detach_tks(tks);
	cur = detach;
	while (cur)
	{
		if ((tk(cur)->type & (TOKEN_LITERAL | TOKEN_TEMPLATE)))
			is_expandable = 0;	
		cur = cur->next;
	}
	join69(detach);
	tk(detach)->type = TOKEN_WORD;
	attach(tks, detach);
	return is_expandable;
	
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
