#ifndef CMD_H
# define CMD_H

#include "list.h"
#include "vector.h"
typedef struct s_cmd
{
	t_vec words;
	t_list *red;
} t_cmd;


t_cmd *get_cmd(t_list *node);
#endif