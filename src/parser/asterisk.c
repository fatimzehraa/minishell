#include "list.h"
#include "minishell.h"
#include "str.h"
#include "token.h"
#include <dirent.h>
#include "parser.h"

int	get_next_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	match_asterisk(char *str, t_list *tks)
{
	int	n;

	while (tks && tk(tks)->type == TOKEN_ASTERISK)
		tks = tks->next;
	if (tks == NULL || tk(tks)->type != TOKEN_WORD)
		return (1);
	while (*str)
	{
		n = get_next_char(str, tk(tks)->str.val[0]);
		if (n == -1)
			return (0);
		if (is_match(str + n, tks))
			return (1);
		str += n + 1;
	}
	return (0);
}

int str_ppsame(t_str *s1, char *s2, int s2_size)
{
	int i;
	i = 0;
	while (i < s2_size) {
		if (s1->val[i] != s2[i])	
			return i; 
		i++;
	}
	return i;
}

int	is_match(char *str, t_list *tks)
{
	int	n;

	while (tks)
	{
		if (tk(tks)->type == TOKEN_ASTERISK)
			return (match_asterisk(str, tks));
		else if (tk(tks)->type == TOKEN_WORD)
		{
			n = str_ppsame(&tk(tks)->str, str, ft_strlen(str));
			if (n == 0)
				return (0);
			str += n;
			tks = tks->next;
		}
		else
			break ;
	}
	return (*str == 0);
}


t_list	*match(t_list *tks)
{
	DIR				*dp;
	struct dirent	*entry;
	t_list			*head;
	t_list			*cur;

	dp = opendir(".");
	if (dp == NULL)
		return (NULL);
	head = NULL;
	while (1)
	{
		entry = readdir(dp);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' && is_match(entry->d_name, tks))
		{
			cur = new_token(ft_strndup(entry->d_name, -1));
			if (cur == NULL)
				break ;
			tk(cur)->type = TOKEN_WORD;
			tk(cur)->has_space = 1;
			ft_lstadd_back(&head, cur);
		}
	}
	if (cur == NULL)
		ft_lstclear(&head, free_token);
	return (closedir(dp), head);
}

