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

void	execute_env(t_ctx *ctx, t_vec cmd)
{
	int i;

	i = 0;
	if (cmd.content[1])
	{
		exit_status = 1;
		return ;
	}
	while (ctx->env.content[i])
	{
		printf("%s\n", (char *)ctx->env.content[i]);
		i++;
	}
	exit_status = 0;
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

char *get_envOrNull(t_vec *env, char *var)
{
	int		holder;

	holder = search_vec(env, var, ft_strlen(var));
	if (holder == -1)
		return NULL;
	else
		return env->content[holder] + ft_strlen(var) + 1;
}

void	execute_pwd(t_ctx *ctx)
{
	char	*cwd;

	cwd = get_envOrNull(&ctx->env, "PWD");
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		return ;
	}
	cwd =  getcwd(NULL, 0);
	if (cwd == NULL)
		perror("minishell: ");
	else
		printf("%s\n", cwd);
	free(cwd);
}
/*
void	execute_cd(t_ctx *ctx, t_vec *cmd)
{
	int	pos;
	int		env_r;
	char	*home;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (cmd->content[1] == NULL)
	{
		pos = search_vec(&ctx->env, "HOME", 4);
		home = ctx->env.content[pos] + 5;
		vec_add(cmd, ft_strndup(home, ft_strlen(home)));
	}
	if (chdir(cmd->content[1]) != 0)
		printf("minishell: cd: %s: %s\n", (char *)cmd->content[1], strerror(errno));
	pos = search_vec(&ctx->env, "PWD", 3);
	env_r = env_replace(&ctx->env, getcwd(NULL, 0), pos);
	pos = search_vec(&ctx->env, "OLDPWD", 6);
	env_r = env_replace(&ctx->env, oldpwd, pos);
	(void)env_r;
}
*/

void _cd(t_ctx *ctx, char *path)
{
	char	*oldpwd;
	char	*pwd;
	int		pos;
	
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		perror("minishell: ");
		exit_status = 1;
		return;
	}
	if (chdir(path) == -1)
	{
		exit_status = 1;
		ft_putstr(2, "minishell: cd: ");
		ft_putstr(2, path);
		perror(": ");
		free(oldpwd);
		return;
	}
	pos = search_vec(&ctx->env, "PWD", 3);
	pwd = getcwd(NULL, 0);
	env_replace(&ctx->env, pwd, pos);
	pos = search_vec(&ctx->env, "OLDPWD", 6);
	env_replace(&ctx->env, oldpwd, pos);
	free(pwd);
	free(oldpwd);
}

void cd(t_ctx *ctx, t_vec *cmd)
{
	char *path;
	if (cmd->size == 1)
	{
		path = get_envOrNull(&ctx->env, "HOME");
		if (path == NULL)
		{
			ft_putstr(2, "HOME env not setted");
			exit_status = 2;
			return ;
		}
		_cd(ctx, path);
	}
	else if (ft_strncmp(cmd->content[1], "-", 2) == 0)
	{
		path = get_envOrNull(&ctx->env, "OLDPWD");
		if (path == NULL)
		{
			ft_putstr(2, "OLDPWD env not setted");
			exit_status = 2;
			return ;
		}
		_cd(ctx, path);
	}
	else
		_cd(ctx, cmd->content[1]);
}

void	execute_cd(t_ctx *ctx, t_vec *cmd)
{
	cd(ctx, cmd);
// 	int	pos;
// 	//int		env_r;
// 	char	*home;
// 	static char		*cwd;
// 	char	*oldpwd;
//
// 	oldpwd = getcwd(NULL, 0);
// //	if (oldpwd == NULL)
// //		printf("minishell: cd: %s: %s\n", (char *)cmd->content[1], strerror(errno));
// 		//oldpwd = cwd;
// //	printf("oldpwd :%s\n", oldpwd);
// 	if (cmd->content[1] == NULL)
// 	{
// 		pos = search_vec(&ctx->env, "HOME", 4);
// 		home = ctx->env.content[pos] + 5;
// 		vec_add(cmd, ft_strndup(home, ft_strlen(home)));
// 	}
// 	if (oldpwd == NULL || chdir(cmd->content[1]) == -1)
// 	{
// 		printf("minishell: cd: %s: %s\n", (char *)cmd->content[1], strerror(errno));
// 		return ;
// 	}
// 	pos = search_vec(&ctx->env, "PWD", 3);
// 	cwd = getcwd(NULL, 0);
// 	if (cwd == NULL)
// 	{
// 		puts("error");
// 		return ;
// 	}
// 	//env_r = 
// 	env_replace(&ctx->env, cwd, pos);
// 	pos = search_vec(&ctx->env, "OLDPWD", 6);
// 	//env_r = 
// 	env_replace(&ctx->env, oldpwd, pos);
// 	//(void)env_r;
// 	oldpwd = cwd;
}
