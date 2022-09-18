#include "list.h"
#include "str.h"
#include "token.h"
#include "parser.h"
#include <stdlib.h>
#include "minishell.h"

int	until(char *str, char *limits)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(limits, str[i]))
			break ;
		i++;
	}
	return (i);
}

int	expand_template(t_list *curr, t_ctx *ctx)
{
	(void) ctx;
	(void) curr;
	char	*str;
	t_str	env;

	env = tk(curr)->str;
	str = env.val;
	str_mk(&tk(curr)->str, "");
	tk(curr)->type = TOKEN_WORD;

	while (*str) {
		env.val = str;
		if (*str == '$' && is_var(str + 1))
		{
			env.val++;
			env.size = var_len(++str);
			str += env.size;
			env = get_env(&env, &ctx->env);
		}
		else {
			env.size = until(str, "$");
			str += env.size;
		}
		str_push(&tk(curr)->str, &env);
	}
	return 1;
}

int	expand(t_list *tokens, t_ctx *ctx)
{
	t_list	*curr;
	
	curr = tokens;
	while (curr)
	{
		if (tk(curr)->type == TOKEN_VAR)
			tk(curr)->str = get_env(&tk(curr)->str, &(ctx->env));
		else if (tk(curr)->type == TOKEN_TEMPLATE)
			expand_template(curr, ctx);
		curr = curr->next;
	}
	return (1);
}
