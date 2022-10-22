#include "list.h"
#include "minishell.h"
#include "str.h"
#include "token.h"
#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>

void	red_out(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[1]);
	fd = open(tk(reds->next)->str.val, O_TRUNC| O_WRONLY| O_CREAT, 0666);
	if (fd == -1)
	{
		perror("minishell");
		return ;
	}
	cmd_fd[1] = fd;
}

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

void	append();

void	heredoc(t_list *reds, int cmd_fd[])
{
	char	*delimiter;
	int		fd;
	char	*line;

	delimiter = reds->next->content;
	fd = open("tmp", O_CREAT | O_WRONLY, 0666);
	while (1)
	{
		line = readline(">");
		if (ft_strncmp(line, delimiter, -1) == 0)
		{
			puts("ass");
			break;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		//rl_redisplay();
	}
	red_out(reds, cmd_fd, fd);
}

void	redirect(t_list *reds, int cmd_fd[])
{
	int	fd = 0;

	while (reds)
	{
		if (tk(reds)->type == TOKEN_RED_OUT)
			red_out(reds, cmd_fd, fd);
		else if (tk(reds)->type == TOKEN_RED_IN)
			red_in(reds, cmd_fd, fd);
		else if (tk(reds)->type == TOKEN_HEREDOC)
			heredoc(reds, cmd_fd);
		reds = reds->next;
	}
}
