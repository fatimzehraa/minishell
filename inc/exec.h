#ifndef EXEC_H
#define EXEC_H
# include "minishell.h"
# include "cmd.h"

int execute(t_list *cmds, t_ctx *ctx);
void	execute_env(t_vec env);
void	execute_export(t_ctx *ctx, t_vec cmd);
void	execute_unset(t_ctx *ctx, t_vec cmd);
void	execute_pwd();
void	execute_cd(t_ctx *ctx, t_vec *cmd);
#endif // !EXEC_H
