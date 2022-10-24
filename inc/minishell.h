#ifndef MINISHELL_H
#define MINISHELL_H
# include"list.h"
#include "str.h"
#include "vector.h"
#include <sys/signal.h>
#include <term.h>

typedef struct s_ctx
{
	t_vec	env;
	struct	sigaction old_act;
	struct	termios restore;
	unsigned char	exit_status;
} t_ctx;

int		clone_env(char **envp, t_vec *env);
void	setup_signals();
char	*get_env(char *var, t_vec *env);
void	setup_signals(t_ctx *ctx);
struct sigaction switch_handler(t_ctx *ctx);
extern int exit_status;
#endif // !MINISHELL_H
