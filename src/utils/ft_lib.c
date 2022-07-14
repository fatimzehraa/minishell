#include <stdlib.h>

void	*ft_realloc(void *mem, int size, int append)
{
	char	*from;
	char	*to;
	int		i;

	from = (char *)mem;
	to = malloc(sizeof(char *) * (size + append));
	if (to == NULL)
		return (NULL);
	i = 0;
	while (i < (size * 8))
	{
		to[i] = from[i];
		i++;
	}
	free(mem);
	return (to);
}

