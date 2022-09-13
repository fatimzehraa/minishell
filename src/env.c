#include "minishell.h"
#include <stdlib.h>
#include "list.h"
#include "str.h"

int	clone_env(char **envp, t_vec *env)
{
	(void) envp;
	(void) env;
	return (0);
}
//
//
//
//t_list	*clone(char **env)
//{
//	int		i;
//	t_list	*lst_env;
//
//	lst_env = NULL;
//	i = 0;
//	while (env[i])
//	{
//		ft_lstadd_back(&lst_env, ft_lstnew(env[i]));
//		i++;
//	}
//	return (lst_env);
//}
////TODO 
//char	*get_env(char	*var, t_list *lst_env)
//{
//	t_list	*curr;
//	char	*value;
//
//	value = NULL;
//	curr = lst_env;
//	while (curr)
//	{
//		if (ft_strncmp(var, curr->content, ft_strlen(var)))
//		{
//			value = getenv(curr->content);
//			break ;
//		}
//		curr = curr->next;
//	}
//	return (value);
//}
//
