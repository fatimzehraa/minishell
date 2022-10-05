#ifndef PARSER_H
# define PARSER_H
# include"list.h"
# include"minishell.h"

t_list	*parser(t_list *tokens, t_ctx *ctx);
int		expand(t_list *tokens, t_ctx *ctx);
t_str	get_env(t_str *str, t_vec *env);
t_list	*join(t_list *tks);
int		until(char *str, char *limits);

#endif
