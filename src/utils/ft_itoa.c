/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:56:28 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 18:56:29 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	count_size(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(unsigned int n)
{
	char	*ascii_s;
	int		i;

	i = count_size(n);
	ascii_s = malloc(i * sizeof(char) + 1);
	if (ascii_s == NULL)
		return (NULL);
	ascii_s[i--] = 0;
	while (i >= 0)
	{
		ascii_s[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (ascii_s);
}
