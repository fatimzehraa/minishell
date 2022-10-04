#include "list.h"
#include "str.h"
#include "token.h"
#include "parser.h"
#include <stdlib.h>
#include "minishell.h"
#include "utils.h"

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

int expand_var(t_ctx *ctx, t_list *token)
{
	t_list	*next;
	char	*value;
	t_list	*node;
	int		has_space;

	has_space = tk(token)->has_space;
	node  = token;
	next = token->next;
	token->next = NULL;
	value = get_env(&tk(token)->str, &ctx->env).val;
	free(tk(token)->str.val);
	while(*value)
	{
		str_init(&tk(node)->str);
		if (get_next_word(&tk(node)->str, &value) == 0)
			return (0);
		tk(node)->has_space = 1;
		tk(node)->type = TOKEN_WORD;
		ft_lstadd_back(&token, node);
		if (*value == '\0')
			break;
		node = new_token(NULL);
	}
	tk(node)->has_space = has_space;
	ft_lstadd_back(&token, next);
	return (1);
}

int	expand(t_list *tokens, t_ctx *ctx)
{
	t_list	*curr;
	
	curr = tokens;
	while (curr)
	{
		if (tk(curr)->type == TOKEN_VAR)
			expand_var(ctx, curr);
		else if (tk(curr)->type == TOKEN_TEMPLATE)
			expand_template(curr, ctx);
		curr = curr->next;
	}
	return (1);
}
