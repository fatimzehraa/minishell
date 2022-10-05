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
			env = get_senv(&env, &ctx->env);
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
	value = get_senv(&tk(token)->str, &ctx->env).val;
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

t_list	*match(t_list *tks);

void expand_asterisk(t_list *tks)
{
	t_list	*curr;
	t_list	*begin;
	t_list	*next;
	
	curr = tks;
	begin = tks;
	while (curr)
	{
		if (tk(curr)->type == TOKEN_ASTERISK)
		{
			next = curr;
			while (tk(next)->type & (TOKEN_ASTERISK | TOKEN_WORD))
			{
				if (!tk(next)->has_space)
				{
					next = next->next;
					break;
				}
				next = next->next;
			}
			t_list *res = match(begin->next);
			if (res)
			{
				begin->next = res;
				ft_lstadd_back(&res, next);
			}
			else
			{
				while (curr != next)
				{
					if (tk(curr)->type == TOKEN_ASTERISK)
					{
						tk(curr)->type = TOKEN_WORD;
						str_pnclone(&tk(curr)->str, "*", 1);
					}
					curr = curr->next;
				}
			}
		}
		if (tk(curr)->has_space)
			begin = curr;
		curr = curr->next;
	}
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
	expand_asterisk(tokens);
	return (1);
}
