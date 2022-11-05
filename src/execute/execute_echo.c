#include <unistd.h>
#include <str.h>
#include "exec.h"

void	print_words(int i, char **words)
{
	while (words[i])
	{
		ft_putstr(1, words[i]);
		if (words[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	execute_echo(t_vec *cmd)
{
	int		i;
	char	*command;

	command = (char *)cmd->content[1];
	i = (command && command[0] == '-');
	if (command)
	{
		while (command && command[i] == 'n')
			i++;
		if (command[i] != 'n' && command[i])
			{
				print_words(1, (char **)cmd->content);
				write(1, "\n", 1);
			}
		else
			print_words(2, (char **)cmd->content);
	}
	else
	write(1, "\n", 1);
}
