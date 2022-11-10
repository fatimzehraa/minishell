/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:54:18 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:54:19 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "str.h"
#include "token.h"
#include "parser.h"
#include <stdlib.h>
#include "minishell.h"
#include "utils.h"

void	handle_template(t_ctx *ctx, t_str *env, char **str)
{
	env->val++;
	env->size = var_len((*str) + 1);
	(*str)++;
	(*str) += env->size;
	*env = get_senv(env, &ctx->env);
}

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
	while (*str)
	{
		env.val = str;
		if (*str == '$' && is_var(str + 1))
			handle_template(ctx, &env, &str);
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
