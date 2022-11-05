#include "minishell.h"
#include "list.h"
#include "exec.h"
#include <stdio.h>
#include <readline/readline.h>
#include "str.h"
#include "token.h"
#include <fcntl.h>
#include <unistd.h>

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

void	heredoc(t_list *tks)
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
		line = readline(">");
		if (line == NULL || str_psame(delimiter, line, ft_strlen(line)))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	str_free(&tk(tks->next)->str);
	str_mk(&tk(tks->next)->str, file_name);
}

void	read_heredocs(t_list *tokens)
{
	while (tokens)
	{
		if (tk(tokens)->type == TOKEN_HEREDOC)
			heredoc(tokens);
		tokens = tokens->next;
	}
}
