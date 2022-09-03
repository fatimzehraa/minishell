#include "list.h"
#include "str.h"
#include "token.h"
#include "parser.h"
#include <stdlib.h>


//push
//TODO 
char	*get_env(char	*value)
{
	(void)value;
	return ("mamak");
}

char	*expand_literal(t_list	*curr)
{
	char	*literal;

	literal = ft_strndup(tk(curr)->value + 1, tk(curr)->len - 2);
	free(tk(curr)->value);
	return (literal);
}

int	until(char *str, char *limits)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(limits, str[i]))
			break ;
		i++;
	}
	return (i);
}

char	*expand_template(t_list *curr)
{
	char	*str;
	char	*template;
	int		len;
	int		v_len;

	template = ft_strndup("", 0);
	str = tk(curr)->value + 1;
	while (*str && *str != '\"')
	{
		if (*str == '$' && is_var(str + 1))
		{
			v_len = var_len(str + 1) + 1;
			len = ft_strlen(get_env(ft_strndup(str, v_len)));
			template = ft_strjoin(template, get_env(ft_strndup(str, v_len)), len);
			str += v_len;
		}
		else
		{
			len = until(str, "$\"");
			template = ft_strjoin(template, str, len);
			str += len;
		}
	}
	return (template);
}

int	expand(t_list *tokens)
{
	t_list	*curr;
	
	curr = tokens;
	while (curr)
	{
		if (tk(curr)->type == TOKEN_VAR)
			tk(curr)->value = get_env(tk(curr)->value);
		else if (tk(curr)->type == TOKEN_LITERAL)
			tk(curr)->value = expand_literal(curr);
		else if (tk(curr)->type == TOKEN_TEMPLATE)
			tk(curr)->value = expand_template(curr);
		curr = curr->next;
	}
	return (1);
}
