#include "str.h"
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	has_chars(char c, char *chrs)
{
	int	i;

	i = 0;
	while (chrs[i])
	{
		if (chrs[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (n == -1)
		n = ft_strlen(s2);
	if (n < 1)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

void	ft_strncpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}

char	*ft_strndup(char *src, int len)
{
	char	*ret;

	if (src == NULL)
		return (NULL);
	if (len == -1)
		len = ft_strlen(src);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strncpy(ret, src, len);
	return (ret);
}

