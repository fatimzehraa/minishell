#include "list.h"

t_list *delete_cur(t_list *list, void (*f)(void *))
{
	t_list *next;

	next = list->next;
	ft_lstdelone(list, f);
	return next;
}

