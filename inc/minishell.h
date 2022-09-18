#ifndef MINISHELL_H
#define MINISHELL_H
# include"list.h"
#include "str.h"
#include "vector.h"

typedef struct s_ctx
{
	t_vec env;
} t_ctx;

int		clone_env(char **envp, t_vec *env);
t_str	get_env(t_str *str, t_vec *env);
void	setup_signals();
#endif // !MINISHELL_H
