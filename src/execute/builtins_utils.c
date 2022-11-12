/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:58:11 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/12 15:42:16 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <stdio.h>
#include "parser.h"
#include "str.h"
#include "token.h"

void	print_var(char *var, int size)
{
	printf("declare -x %.*s", size, var);
	if (var[size] == '\0')
	{
		printf("\n");
		return ;
	}
	var += size + 1;
	printf("=\"");
	while (*var)
	{
		size = until(var, "\"");
		printf("%.*s", size, var);
		var += size;
	}
	printf("\"\n");
}

char	*get_val(char *s)
{
	int	u;

	u = until(s, "+=");
	if (s[u] == '+')
		u++;
	if (s[u] == '=')
		u++;
	return (s + u);
}

int	search_and_replace(t_vec *env, char *var)
{
	int		pos;
	int		i;
	char	*s;

	g_exit_status = 1;
	if (!is_var(var) || (var[var_len(var)] != '\0' && var[var_len(var)] != '='
			&&!(var[var_len(var)] == '+' && var[var_len(var) + 1] == '=')))
		return (ft_putstr(2, "syntax error\n"), 0);
	g_exit_status = 0;
	i = until(var, "+=");
	pos = search_vec(env, var, i);
	if (pos == -1)
		return (vec_add(env, var), 1);
	if (var[i] == '\0')
		return (1);
	s = ft_strndup(env->content[pos], -1);
	if (var[i] == '+')
	{
		s = ft_strjoin(s, get_val(var), -1);
		env_replace(env, s, pos);
		free(s);
		return (1);
	}
	env_replace(env, get_val(var), pos);
	return (free(s), 1);
}

int	env_replace(t_vec *env, void *new_value, int pos)
{
	int		size;
	char	*new;

	size = until(env->content[pos], "=");
	if (new_value == NULL)
	{
		new = malloc((size + 1) * sizeof(char));
		if (new == NULL)
			return (0);
		ft_strncpy(new, env->content[pos], 1);
		return (1);
	}
	new = malloc((size + ft_strlen(new_value) + 2));
	if (new == NULL)
		return (0);
	ft_strncpy(new, env->content[pos], size);
	ft_strncpy(new + size, "=", size);
	ft_strncpy(new + size + 1, new_value, ft_strlen(new_value));
	free(env->content[pos]);
	env->content[pos] = new;
	return (1);
}
