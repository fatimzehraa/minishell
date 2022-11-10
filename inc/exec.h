/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:22:18 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 20:22:20 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"
# include "cmd.h"

int		check_syntax(t_list *cmds);
void	ft_dup(t_list *cmds, int cmd_fd[], int fd_in);
int		ft_wait(t_ctx *ctx, pid_t pid);
int		is_dir(char *filename);
char	*get_command(t_ctx *ctx, t_list *cmds);
int		execute(t_list *cmds, t_ctx *ctx);
void	ft_exec_child(t_ctx *ctx, t_list *cmds, char *cmd, int cmd_fd[]);
void	execute_env(t_ctx *ctx, t_vec cmd);
void	execute_export(t_ctx *ctx, t_vec cmd);
void	execute_unset(t_ctx *ctx, t_vec cmd);
void	execute_pwd(t_ctx *ctx);
void	execute_cd(t_ctx *ctx, t_vec *cmd);
void	execute_echo(t_vec *cmd);
void	execute_exit(t_ctx *ctx, t_vec cmd);
void	print_var(char *var, int size);
char	*get_val(char *s);
void	search_and_replace(t_vec *env, char *var);
int		env_replace(t_vec *env, void *new_value, int pos);
void	redirect(t_list *reds, int cmd_fd[]);
void	get_next_comb(char *s);
char	*get_tmp(void);
t_list	*detach_tks(t_list *tks);
void	attach(t_list *lst, t_list *node);
int		join_here(t_list *tks);
int		expand_template(t_list *curr, t_ctx *ctx);
#endif // !EXEC_H
