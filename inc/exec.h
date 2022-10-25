#ifndef EXEC_H
#define EXEC_H
# include "minishell.h"
# include "cmd.h"

int execute(t_list *cmds, t_ctx *ctx);
void ft_exec_child(t_ctx *ctx, t_list *cmds, char *cmd, int cmd_fd[], int fd_in);
void	execute_env(t_ctx *ctx, t_vec cmd);
void	execute_export(t_ctx *ctx, t_vec cmd);
void	execute_unset(t_ctx *ctx, t_vec cmd);
void	execute_pwd();
void	execute_cd(t_ctx *ctx, t_vec *cmd);
void	execute_exit(t_ctx *ctx, t_vec cmd);
void	print_var(char *var, int size);
char *get_val(char *s);
void	search_and_replace(t_vec *env, char *var);
int env_replace(t_vec *env, void *new_value, int pos);
void	redirect(t_list *reds, int cmd_fd[]);
#endif // !EXEC_H
