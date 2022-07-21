/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatimzehra </var/spool/mail/fatimzehra>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:02:21 by fatimzehra        #+#    #+#             */
/*   Updated: 2022/07/21 18:54:59 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "list.h"
#include "str.h"
#include "token.h"
void	exec_line(char *cmd)
{
	t_list	*tokens;

	tokens = tokenizer(cmd);
	//if (check_syntax(tokens)) continue
	//t_list command parser(tokens)
	//void execute(command)
	while (tokens)
	{
		printf("content: %s\n    type: %d\n", tk(tokens)->value, tk(tokens)->type);
		tokens = tokens->next;
	}
}
