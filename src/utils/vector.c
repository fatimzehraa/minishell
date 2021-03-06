#include "str.h"
#include "vector.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void	free_vec(t_vec *vec)
{
	int	i;

	if (vec->size <= 0)
		return ;
	i = 0;
	while (vec->content[i])
	{
		free(vec->content[i]);
		i++;
	}
	free(vec->content);
}

void vec_rem(t_vec *vec, int pos)
{
	int i;

	if (pos >= vec->len)
	{
		printf("abort\n");
		exit(2); 
	}
	i = pos;
	while (i < vec->len) {
		vec[i] = vec[i + 1];
		i++;
	}
	vec->len--;
}

int	vec_add(t_vec *arr, void *new_value)
{
	if (arr->len + 1 >= arr->size)
	{
		arr->content = ft_realloc(arr->content, arr->size, arr->defsize);
		if (arr->content == NULL)
			return (0);
		arr->size += arr->defsize;
	}
	arr->content[arr->len] = new_value;
	if (new_value != NULL)
	{
		arr->len++;
		vec_add(arr, NULL);
	}
	return (1);
}

void	init_vec(t_vec *arr, int defsize)
{
	arr->content = NULL;
	arr->len = 0;
	arr->size = 0;
	arr->defsize = defsize;
}

int	search_vec(t_vec *arr, char *name)
{
	int	i;

	i = 0;
	while (arr->content[i])
	{
		if (ft_strncmp(arr->content[i], name, ft_strlen(name)) == 0
			&& (((char *)arr->content[i])[ft_strlen(name)] == '='
			|| ((char *)arr->content[i])[ft_strlen(name)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

