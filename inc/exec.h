#ifndef EXEC_H
#define EXEC_H
# include "minishell.h"
# include "cmd.h"

int execute(t_list *cmds, t_ctx *ctx);
void	execute_cd(t_vec cmd);
#endif // !EXEC_H
