/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:25:34 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/11 15:44:55 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "parser.h"
#include "vector.h"
#include "exec.h"

void	execute_env(t_ctx *ctx, t_vec cmd)
{
	int	i;

	i = 0;
	if (cmd.content[1])
	{
		g_exit_status = 1;
		return ;
	}
	while (ctx->env.content[i])
	{
		printf("%s\n", (char *)ctx->env.content[i]);
		i++;
	}
	g_exit_status = 0;
}

void	execute_export(t_ctx *ctx, t_vec cmd)
{
	int		i;
	int		j;
	char	**content;

	content = (char **)ctx->env.content;
	if (cmd.content[1] == NULL)
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
			search_and_replace(&ctx->env, ft_strndup(cmd.content[j], -1));
			j++;
		}
	}
}

void	execute_unset(t_ctx *ctx, t_vec cmd)
{
	int	pos;
	int	i;

	i = 1;
	while (cmd.content[i])
	{
		pos = search_vec(&ctx->env, cmd.content[i], ft_strlen(cmd.content[i]));
		if (pos != -1)
			vec_rem(&ctx->env, pos);
		i++;
	}
}
