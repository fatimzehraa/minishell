#ifndef UTILS_H
# define UTILS_H

# include "str.h"

void	*ft_realloc(void *mem, int size, int append);
int		until(char *str, char *limits);
int		get_next_word(t_str *str, char **s_ptr);
#endif
