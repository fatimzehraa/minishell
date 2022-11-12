/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:58:17 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/12 15:34:59 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "minishell.h"
#include <dirent.h>
#include "exec.h"
#include "str.h"
#include "vector.h"
#include <errno.h>
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	*get_env_or_null(t_vec *env, char *var)
{
	int		holder;

	holder = search_vec(env, var, ft_strlen(var));
	if (holder == -1)
		return (NULL);
	else
		return (env->content[holder] + ft_strlen(var) + 1);
}

void	execute_pwd(t_ctx *ctx)
{
	char	*cwd;

	cwd = get_env_or_null(&ctx->env, "PWD");
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("minishell: ");
	else
		printf("%s\n", cwd);
	free(cwd);
}

int	_cd(t_ctx *ctx, char *path)
{
	char	*oldpwd;
	char	*pwd;
	int		pos;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (perror("minishell: "), 1);
	if (chdir(path) == -1)
	{
		ft_putstr(2, "minishell: cd: ");
		ft_putstr(2, path);
		return (perror(": "), free(oldpwd), 1);
	}
	pos = search_vec(&ctx->env, "PWD", 3);
	if (pos == -1)
		vec_add(&ctx->env, ft_strndup("PWD=", -1));
	pos = search_vec(&ctx->env, "PWD", 3);
	pwd = getcwd(NULL, 0);
	env_replace(&ctx->env, pwd, pos);
	pos = search_vec(&ctx->env, "OLDPWD", 6);
	if (pos == -1)
		vec_add(&ctx->env, ft_strndup("OLDPWD=", -1));
	pos = search_vec(&ctx->env, "OLDPWD", 6);
	env_replace(&ctx->env, oldpwd, pos);
	return (free(pwd), free(oldpwd), 0);
}

void	execute_cd(t_ctx *ctx, t_vec *cmd)
{
	char	*path;

	g_exit_status = 2;
	if (cmd->size == 1)
	{
		path = get_env_or_null(&ctx->env, "HOME");
		if (path == NULL)
		{
			ft_putstr(2, "HOME env not setted");
			return ;
		}
		g_exit_status = _cd(ctx, path);
	}
	else if (ft_strncmp(cmd->content[1], "-", 2) == 0)
	{
		path = get_env_or_null(&ctx->env, "OLDPWD");
		if (path == NULL)
		{
			ft_putstr(2, "OLDPWD env not setted");
			return ;
		}
		g_exit_status = _cd(ctx, path);
	}
	else
		g_exit_status = _cd(ctx, cmd->content[1]);
}
