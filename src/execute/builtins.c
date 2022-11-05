#include "cmd.h"
#include "minishell.h"
#include <dirent.h>
#include "exec.h"
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

void	execute_pwd()
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		puts("error");
	else
		printf("%s\n", cwd);
	free(cwd);
}

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
