#include "list.h"
#include "parser.h"
#include "minishell.h"

t_list	*parser(t_list *tokens, t_ctx *ctx)
{

	expand(tokens, ctx);
	join(tokens);
	return (tokens);
}
