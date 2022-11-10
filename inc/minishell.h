/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:20:26 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 20:21:28 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include"list.h"
# include "str.h"
# include "vector.h"
# include <sys/signal.h>
# include <term.h>

typedef struct s_ctx
{
	t_vec				env;
	struct sigaction	old_act;
	struct termios		restore;
}	t_ctx;

int					clone_env(char **envp, t_vec *env);
char				*get_env(char *var, t_vec *env);
void				setup_signals(t_ctx *ctx);
struct sigaction	switch_handler(t_ctx *ctx);
extern int			g_exit_status;
#endif // !MINISHELL_H
