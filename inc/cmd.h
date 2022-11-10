/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:22:03 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 20:22:05 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "list.h"
# include "vector.h"

typedef struct s_cmd
{
	t_vec	words;
	t_list	*red;
}	t_cmd;

t_cmd	*get_cmd(t_list *node);
#endif
