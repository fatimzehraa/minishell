#include "list.h"
#include "str.h"
#include "token.h"
#include "parser.h"
#include <stdlib.h>
#include "minishell.h"
#include "utils.h"

int	expand_template(t_list *curr, t_ctx *ctx)
{
	char	*str;
	t_str	env;
	char	*tmp;

	env = tk(curr)->str;
	if (!str_mk(&tk(curr)->str, ""))
		return (free(env.val), 0);
	str = env.val;
	tmp = str;
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
		else
		{
			env.size = until(str, "$");
			str += env.size;
		}
		if (str_push(&tk(curr)->str, &env) == 0)
			return (free(env.val), 0);
	}
	return (free(tmp), 1);
}

/*
 * ft_lstadd_back has an extra protection
 * if we try list and new point to the same list
 * it will just ignore them and do nothing
 * not a good idea thought (but norm)
*/
int expand_var(t_ctx *ctx, t_list *token)
{
	t_list	*next;
	char	*value;
	t_list	*node;
	int		has_space;

	has_space = tk(token)->has_space;
	next = token->next;
	token->next = NULL;
	value = get_senv(&tk(token)->str, &ctx->env).val;
	if (value == NULL)
		return 0;
	free(tk(token)->str.val);
	node  = token;
	while(1)
	{
		str_init(&tk(node)->str);
		if (get_next_word(&tk(node)->str, &value) == 0)
			return (ft_lstadd_back(&token, next), 0);
		tk(node)->has_space = 1;
		tk(node)->type = TOKEN_WORD;
		ft_lstadd_back(&token, node);
		if (*value == '\0')
			break;
		node = new_token(NULL);
		if (node == NULL)
			return (ft_lstadd_back(&token, next), 0);
	}
	tk(node)->has_space = has_space;
	ft_lstadd_back(&token, next);
	return (1);
}

t_list *_expand_asterisk(t_list *curr, t_list *begin)
{
	t_list	*res;
	t_list	*next;

	next = curr;
	while (tk(next)->type & (TOKEN_ASTERISK | TOKEN_WORD) && tk(next)->has_space == 0)
		next = next->next;
	next = next->next;
	res = match(begin->next);
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
				tk(curr)->type = TOKEN_WORD;
			curr = curr->next;
		}
	}
	return curr;
}

/*
 * 1. search for *
 * 2. get end of expression
 * 3. match
 * 4. link
 */
int expand_asterisk(t_list *tks)
{
	t_list	*curr;
	t_list	*head;
	
	curr = tks;
	head = tks;
	while (curr)
	{
		if (tk(curr)->type == TOKEN_ASTERISK)
			curr = _expand_asterisk(curr, head);
		if (tk(curr)->has_space)
			head = curr;
		curr = curr->next;
	}
	return 1;
}

int	expand(t_list *tokens, t_ctx *ctx)
{
	t_list	*curr;
	
	curr = tokens;
	while (curr)
	{
		if (tk(curr)->type == TOKEN_LITERAL)
			tk(curr)->type = TOKEN_WORD;
		else if (tk(curr)->type == TOKEN_VAR)
		{
			if (expand_var(ctx, curr) == 0)
				return (ft_lstclear(&tokens, free_token), 0);
		}
		else if (tk(curr)->type == TOKEN_LITERAL)
			tk(curr)->type = TOKEN_WORD;
		else if (tk(curr)->type == TOKEN_TEMPLATE)
			if (expand_template(curr, ctx) == 0)
				return (ft_lstclear(&tokens, free_token), 0);
		curr = curr->next;
	}
	return (expand_asterisk(tokens));
}
