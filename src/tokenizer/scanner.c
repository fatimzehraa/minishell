/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatimzehra </var/spool/mail/fatimzehra>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:57:03 by fatimzehra        #+#    #+#             */
/*   Updated: 2022/07/21 20:33:24 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "str.h"

int	string_len(char *cmd, char c)
{
	int	len;

	len = 0;
	while (cmd[len] && cmd[len] != c)
		len++;
	if (cmd[len] == c)
		len++;
	return (len);
}

int	var_len(char *cmd)
{
	int	len;

	len = 0;
	if (cmd[0] == '?')
		return (1);
	while (ft_strchr(VAR_CHAR, cmd[len]))
		len++;
	return (len);
}

int	is_var(char *cmd)
{

	if (cmd[0] == '?' || ft_isalpha(*cmd))
		return (1);
	return (0);
}

int word_len(char *cmd)
{
	int	len;

	len = 0;
	if (cmd[len] == '$')
		len++;
	while ( cmd[len] && !ft_strchr("$<>|\'\"", cmd[len]) && (!is_space(cmd[len])))
		len ++;
	return (len);
}
