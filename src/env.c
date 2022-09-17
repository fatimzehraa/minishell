#include "minishell.h"
#include <stdlib.h>
#include "list.h"
#include "str.h"

int	clone_env(char **envp, t_vec *env)
{
	int i;

	init_vec(env, 100);
	i = 0;
	while (envp[i])
	{
		if (vec_add(env, ft_strndup(envp[i], -1)) == 0)
			return (free_vec(env), 0);
		i++;
	}
	return (1);
}

char	*get_env(char *var, t_vec *env)
{
	char	*value;
	int		holder;

	holder = search_vec(env, var);
	if (holder == -1)
		value = ft_strndup("", -1);
	else
		value = ft_strndup(env->content[holder] + ft_strlen(var) + 1, -1);
	return (value);
}

int export(char *new_var, t_vec *env)
{
	return (vec_add(env, ft_strndup(new_var, -1)));
}

void	unset(char *var, t_vec *env)
{
	int	position;

	position = search_vec(env, var);
	vec_rem(env, position);
}
