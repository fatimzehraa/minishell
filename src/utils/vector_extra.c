#include "vector.h"
#include "util.h"
#include "str.h"

int	search_vec_(t_vec *arr, char *name)
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
