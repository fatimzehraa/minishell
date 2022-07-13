/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:21:25 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/13 16:09:05 by fael-bou         ###   ########.fr       */
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
		rl_on_new_line();
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
		add_history(command);
		printf("%s\n", command);
	}
	return 0;
}
