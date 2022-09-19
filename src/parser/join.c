#include "list.h"
#include "str.h"
#include "token.h"


int join_seq(t_str *str, t_list *tks, t_list **plast)
{
	t_list *cur;
	int		has_space;

	cur = tks;
	has_space = 0;
	while (cur && tk(cur)->type == TOKEN_WORD && !has_space)
	{
		has_space = tk(cur)->has_space;
		str_push(str, &tk(cur)->str);
		cur = delete_cur(cur, free_token);
	}
	(*plast)->next = cur;
	*plast = cur;
	return 1;
}

t_list * join(t_list *tks)
{
	t_list *cur;

	cur = tks;
	while (cur)
	{
		if (tk(cur)->type == TOKEN_WORD
				&& tk(cur)->has_space == 0)
			join_seq(&tk(cur)->str, cur->next, &cur);
		else
			cur = cur->next;
	}
	return cur;
}
