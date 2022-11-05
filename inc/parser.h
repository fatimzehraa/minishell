#ifndef PARSER_H
# define PARSER_H
# include"list.h"
# include"minishell.h"

t_list	*parser(t_list *tokens, t_ctx *ctx);
int		expand(t_list *tokens, t_ctx *ctx);
t_str	get_senv(t_str *str, t_vec *env);
t_list	*join(t_list *tks);
int		until(char *str, char *limits);
void	read_heredocs(t_ctx *ctx, t_list *tokens);
t_list	*match(t_list *tks);
int		is_match(char *str, t_list *tks);
t_list	*join69(t_list *tks);

#endif
