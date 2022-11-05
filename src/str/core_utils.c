#include "str.h"
#include <stdlib.h>

void	str_init(t_str *str)
{
	str->val = NULL;
	str->size = 0;
	str->cap = 0;
}

int	str_mk(t_str *str, char *s)
{
	if (s == NULL)
		return (str_init(str), 1);
	str->size = ft_strlen(s);
	str->cap = str->size;
	str->val = ft_strndup(s, str->size);
	if (str->val == 0)
		return (str_init(str), 0);
	return (str->val != 0);
}

int	str_push(t_str *s1, t_str *s2)
{
	int		slot;
	char	*tmp;	

	slot = s1->cap - s1->size;
	if (s2->size >= slot)
	{
		tmp = s1->val;
		s1->val = malloc(sizeof(char *) * (s1->size + s2->size + 20));
		if (s1->val == NULL)
		{
			s1->cap = -1;
			s1->size = -1;
			free(tmp);
			return (0);
		}
		s1->cap = s1->size + s2->size + 20;
		ft_strncpy(s1->val, tmp, s1->size);
		free(tmp);
	}
	ft_strncpy(s1->val + s1->size, s2->val, s2->size);
	s1->size = s1->size + s2->size;
	return (1);
}
