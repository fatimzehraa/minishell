/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:21:25 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/13 17:06:35 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	handler(int sig, siginfo_t *infos, void *ptr)
{
	(void)infos;
	(void)ptr;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main (int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char *command;
	struct sigaction act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	while (1)
	{
		sigaction(SIGQUIT, &act, NULL);
		sigaction(SIGINT, &act, NULL);
		command = readline("$>");
		if (command == NULL)
		{
			printf("exit\n");
			break;
		}
		add_history(command);
		printf("%s\n", command);
	}
	return 0;
}
