#include "cmd.h"
#include "list.h"
#include "minishell.h"
#include <dirent.h>
#include "exec.h"
#include "vector.h"
#include <errno.h>
#include "parser.h"
#include "token.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	execute_env(t_vec env)
{
	int i;

	i = 0;
	while (env.content[i])
	{
		printf("%s\n", (char *)env.content[i]);
		i++;
	}
}

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

	if (!is_var(var) || (var[var_len(var)] != '\0' && var[var_len(var)] != '=' && !(var[var_len(var)] == '+' && var[var_len(var) + 1] == '=')))
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

void	execute_export(t_ctx *ctx, t_vec cmd)
{
	int	i;
	int		j;
	char	**content;

	content = (char **)ctx->env.content;
	if (cmd.content[1] == NULL) //no_param case
	{
		i = 0;
		while (content[i])
		{
			print_var(content[i], until(content[i], "="));
			i++;
		}
	}
	else
	{
		j = 1;
		while (cmd.content[j])
		{
			search_and_replace(&ctx->env, cmd.content[j]);
			j++;
		}
	}
	//else //err 
	{

	}
}

void	execute_cd(t_vec cmd)
{
	int err;

	err = chdir(cmd.content[1]);
	if (err != 0)
		printf("%s\n",strerror(errno));
}
