/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:21:25 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/13 11:34:36 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main (int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char *command;

	while (1)
	{
		command = readline("$>");
		add_history(command);
		printf("%s\n", command);
	}
	return 0;
}
