#include "minishell.h"
#include "token.h"
#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

void	redirect(t_list *reds, int cmd_fd[])
{
	int	fd;
	while (reds)
	{
		if (tk(reds)->type == TOKEN_RED_OUT)
		{
			close(cmd_fd[1]);
			fd = open(tk(reds->next)->str.val, O_RDONLY| O_CREAT, 0666);
			if (fd == -1)
			{
				perror("minishell");
				return ;
			}
			cmd_fd[1] = fd;
		}
		reds = reds->next;
	}
}
