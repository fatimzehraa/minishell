#include "str.h"
#include "vector.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	free_vec(t_vec *vec)
{
	int	i;

	if (vec->cap <= 0)
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

	if (pos >= vec->size)
	{
		printf("abort\n");
		exit(2); 
	}
	i = pos;
	while (i < vec->size) {
		vec[i] = vec[i + 1];
		i++;
	}
	vec->size--;
}

int	vec_add(t_vec *arr, void *new_value)
{
	if (arr->size + 1 >= arr->cap)
	{
		arr->content = ft_realloc(arr->content, arr->cap, arr->defsize);
		if (arr->content == NULL)
			return (0);
		arr->cap += arr->defsize;
	}
	arr->content[arr->size] = new_value;
	if (new_value != NULL)
	{
		arr->size++;
		vec_add(arr, NULL);
	}
	return (1);
}

void	init_vec(t_vec *arr, int defsize)
{
	arr->content = NULL;
	arr->size = 0;
	arr->cap = 0;
	arr->defsize = defsize;
}

int	search_vec(t_vec *arr, char *str, int size)
{
	int	i;

	i = 0;
	while (arr->content[i])
	{
		if (ft_strncmp(str, (char *)arr->content[i], size) == 0
			&& (((char *)arr->content[i])[size] == '='
			|| ((char *)arr->content[i])[size] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

