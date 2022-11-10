/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:22:25 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 20:22:27 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "str.h"

void	*ft_realloc(void *mem, int size, int append);
int		until(char *str, char *limits);
int		get_next_word(t_str *str, char **s_ptr);
#endif
