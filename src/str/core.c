#include "str.h"
#include <stdlib.h>

void str_init(t_str *str)
{
	str->val = NULL;
	str->size = 0;
	str->cap = 0;
}

int str_mk(t_str *str, char *s)
{
	if (s == NULL)
		return (str_init(str), 1);
	str->size = ft_strlen(s);
	str->cap = str->size;
	str->val = ft_strndup(s, str->size);
	if (str->val == 0)
		return (str_init(str), 0);
	return str->val != 0;
}

int str_push(t_str *s1, t_str *s2)
{
	int slot;
	char *tmp;	

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
			return 0;
		}
		s1->cap = s1->size + s2->size + 20;
		ft_strncpy(s1->val, tmp, s1->size);
		free(tmp);
	}
	ft_strncpy(s1->val + s1->size, s2->val, s2->size);
	s1->size = s1->size + s2->size;
	return 1;
}

int str_same(t_str *s1, t_str *s2, int s2_size)
{
	int i;
	if (s1->size < s2_size || s2->size < s2_size)
		return 0;
	i = 0;
	while (i < s2_size) {
		if (s1->val[i] != s2->val[i])	
			return 0; 
		i++;
	}
	return 1;
}

int str_clone(t_str *dest, t_str *src)
{
	char *tmp;

	if (src->size < dest->size)
	{
		ft_strncpy(dest->val, src->val, src->size);
		dest->size = src->size;
		return (1);
	}
	tmp = ft_strndup(src->val, src->size);
	free(dest->val);
	str_init(dest);
	if (tmp == NULL)
		return 0;
	dest->val = tmp;
	dest->size = src->size;
	dest->cap = src->size;
	return (1);
}

int str_pnclone(t_str *dest, char *src, int n)
{
	t_str s;

	s.val = src;
	if (n == -1)
		s.size = ft_strlen(src);
	else
		s.size = n;
	s.cap = s.size;
	return str_clone(dest, &s);
}

int str_psame(t_str *dest, char *src, int len)
{
	t_str s;

	s.val = src;
	s.size = len;
	s.cap = s.size;
	return str_same(dest, &s, len);
}
