/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatimzehra </var/spool/mail/fatimzehra>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:14:19 by fatimzehra        #+#    #+#             */
/*   Updated: 2022/07/24 15:15:15 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "parser.h"
#include "minishell.h"

t_list	*parser(t_list *tokens)
{

	expand(tokens);
	return (tokens);
}
