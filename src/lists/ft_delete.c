#include "list.h"

t_list *delete_cur(t_list *list, void (*f)(void *))
{
	t_list *next;

	if (list == NULL)
		return NULL;
	next = list->next;
	ft_lstdelone(list, f);
	return next;
}

