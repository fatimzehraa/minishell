#include "token.h"
#include "str.h"
#include <string.h>

int	string_len(char *cmd, char c)
{
	int	len;

	len = 0;
	while (cmd[len] && cmd[len] != c)
		len++;
	return (len);
}

int	var_len(char *cmd)
{
	int	len;

	len = 0;
	if (cmd[0] == '?')
		return (1);
	while (cmd[len] 
			&& (ft_isalpha(cmd[len]) || ft_isnum(cmd[len]) || cmd[len] == '_'))
		len++;
	return (len);
}

int	is_var(char *cmd)
{
	if (ft_isnum(*cmd))
		return (0);
	return (cmd[0] == '?' || ft_isalpha(*cmd) || cmd[0] == '_');
}

int word_len(char *cmd)
{
	int	len;

	len = 0;
	if (cmd[len] == '$')
		len++;
	while (cmd[len]
			&& ft_strncmp(cmd + len, "&&", 2) != 0
			&& !ft_strchr("*$<>|" CHAR_SDQ , cmd[len])
			&& (!is_space(cmd[len])))
		len ++;
	while (cmd[len] == '$' && !is_var(cmd +len + 1))
		len++;
	return (len);
}
