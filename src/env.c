#include "minishell.h"
#include <stdlib.h>
#include "list.h"
#include "str.h"


static int	count_size(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(unsigned int n)
{
	char	*ascii_s;
	int		i;

	i = count_size(n);
	ascii_s = malloc(i * sizeof(char) + 1);
	if (ascii_s == NULL)
		return (NULL);
	ascii_s[i--] = 0;
	while (i >= 0)
	{
		ascii_s[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (ascii_s);
}

int	clone_env(char **envp, t_vec *env)
{
	int i;
	char *str;

	init_vec(env, 100);
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

t_str get_senv(t_str *str, t_vec *env)
{
	t_str val;
	int		holder;
	char	*to_find;

	str_init(&val);
	if (str_psame(str, "?", 1))
		to_find = ft_itoa(exit_status);
	else {
		holder = search_vec(env, str->val, str->size);
		if (holder == -1)
			to_find = "";
		else
			to_find =  env->content[holder] + str->size + 1;
	}
	str_pnclone(&val, to_find, -1); 
	return (val);
}

char	*get_env(char *var, t_vec *env)
{
	char	*value;
	int		holder;

	holder = search_vec(env, var, ft_strlen(var));
	if (holder == -1)
		value = ft_strndup("", 0);
	else
		value = ft_strndup(env->content[holder] + ft_strlen(var) + 1, -1);
	return (value);
}


int export(char *new_var, t_vec *env)
{
	return (vec_add(env, ft_strndup(new_var, -1)));
}
