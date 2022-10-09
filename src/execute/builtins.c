#include "cmd.h"
#include "list.h"
#include "minishell.h"
#include <dirent.h>
#include "exec.h"
#include "vector.h"
#include <errno.h>
#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <sys/_types/_errno_t.h>
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

void	execute_export(t_ctx *ctx, t_vec cmd)
{
	int	i;
	char	**content;
	int		pos;

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
	else if (cmd.content[1] != NULL) // one param case
	{
		pos = search_vec(&ctx->env, cmd.content[1], until(cmd.content[1], "="));
		if (pos != -1)
			vec_rem(&ctx->env, pos);
		vec_add(&ctx->env, cmd.content[1]);
	}
	else //err 
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
