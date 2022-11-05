#include "minishell.h"
#include "exec.h"
#include <stdio.h>
#include "parser.h"
#include "token.h"

void	print_var(char *var, int size)
{
	printf("declare -x %.*s", size, var);
	if (var[size] == '\0')
	{
		printf("\n");
		return;
	}
	var += size + 1;
	printf("=\"");
	while (*var) {
		size = until(var, "\"");
		printf("%.*s", size, var);
		var += size;
	}
	printf("\"\n");
}

char *get_val(char *s)
{
	int u;

	u = until(s, "+=");
	if (s[u] == '+')
		u++;
	if (s[u] == '=')
		u++;
	return s+u;
}

void	search_and_replace(t_vec *env, char *var)
{
	int	pos;
	int	i;

	if (!is_var(var) || (var[var_len(var)] != '\0' && var[var_len(var)] != '=' &&
			!(var[var_len(var)] == '+' && var[var_len(var) + 1] == '=')))
	{
		printf("syntax error\n");
		return ;
	}
	i = until(var, "+=");
	pos = search_vec(env, var, i);
	if (pos != -1)
	{
		if (var[i] == '+' && *get_val(env->content[pos]) == '\0')
			env->content[pos] = ft_strjoin(env->content[pos], "===", 1);
		var = ft_strjoin(env->content[pos], get_val(var), ft_strlen(get_val(var)));
		vec_rem(env, pos);
	}
	vec_add(env, var);
}

int env_replace(t_vec *env, void *new_value, int pos)
{
	int size;
	char *new;

//	printf("value is %s, pos is %d", (char *)new_value, pos);
//	return 0;
	size = until(env->content[pos], "=");
	new = ft_strjoin(NULL, env->content[pos], size);
	if (new == NULL)
		return 0;
	new = ft_strjoin(new, "=", 1);
	if (new == NULL)
		return 0;
	new = ft_strjoin(new, new_value, -1);
	if (new == NULL)
		return 0;
	
	free(env->content[pos]);
	env->content[pos] = new;
	return 1;
}
