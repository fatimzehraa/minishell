#ifndef PARSER_H
# define PARSER_H
# include"list.h"
# include"minishell.h"

t_list	*parser(t_list *tokens, t_ctx *ctx);
int	expand(t_list *tokens, t_ctx *ctx);
t_list *join(t_list *tks);
t_list	*match(t_list *tks);
int	is_match(char *str, t_list *tks);

#endif
