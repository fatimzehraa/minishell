#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

void	handler(int sig, siginfo_t *infos, void *ptr)
{
	(void)sig;
	(void)infos;
	(void)ptr;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals()
{
	struct sigaction act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &act, NULL);
}
