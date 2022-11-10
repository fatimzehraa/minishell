/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:54:44 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:54:45 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <sys/signal.h>
#include <unistd.h>

void	handler(int sig, siginfo_t *infos, void *ptr)
{
	(void)sig;
	(void)infos;
	(void)ptr;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

void	setup_signals(t_ctx *ctx)
{
	struct sigaction	act;
	struct sigaction	ign_act;

	signal(SIGQUIT, SIG_IGN);
	act.sa_flags = SA_RESTART;
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	ign_act.sa_flags = SA_RESTART;
	ign_act.sa_handler = SIG_IGN;
	sigemptyset(&ign_act.sa_mask);
	ctx->old_act = ign_act;
}

struct sigaction	switch_handler(t_ctx *ctx)
{
	struct sigaction	oact;

	sigaction(SIGINT, &ctx->old_act, &oact);
	ctx->old_act = oact;
	return (oact);
}
