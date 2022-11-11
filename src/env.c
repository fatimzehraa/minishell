/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:55:58 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/11 18:34:45 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "list.h"
#include "str.h"
#include "vector.h"

int	clone_env(char **envp, t_vec *env)
{
	int		i;
	char	*str;

	init_vec(env, 100);
	if (envp == NULL || envp[0] == NULL)
	{
		if (vec_add(env, NULL) == 0)
			return (0);
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		str = ft_strndup(envp[i], -1);
		if (str == NULL || vec_add(env, str) == 0)
			return (free_vec(env), 0);
		i++;
	}
	return (1);
}

t_str	get_senv(t_str *str, t_vec *env)
{
	t_str	val;
	int		holder;
	char	*to_find;

	str_init(&val);
	if (str_psame(str, "?", 1))
		to_find = ft_itoa(g_exit_status);
	else
	{
		holder = search_vec(env, str->val, str->size);
		if (holder == -1)
			to_find = "";
		else
		{
			to_find = env->content[holder] + str->size;
			if (*to_find == '=')
				to_find++;
		}
	}
	if (to_find == NULL || str_pnclone(&val, to_find, -1) == 0)
		str_init(&val);
	return (val);
}

char	*get_env(char *var, t_vec *env)
{
	char		*value;
	static char	itoa[20];
	int			holder;

	if (ft_strncmp(var, "?", 2) == 0)
	{
		value = ft_itoa(g_exit_status);
		ft_strncpy(itoa, value, ft_strlen(value));
		free(value);
		return (itoa);
	}
	holder = search_vec(env, var, ft_strlen(var));
	if (holder == -1)
		value = "";
	else
		value = env->content[holder] + ft_strlen(var) + 1;
	return (value);
}

int	export(char *new_var, t_vec *env)
{
	return (vec_add(env, ft_strndup(new_var, -1)));
}
