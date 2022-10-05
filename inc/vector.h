#ifndef VECTOR_H
#define VECTOR_H

# include "str.h"

typedef struct s_vec {
	void	**content;
	int		size;
	int		cap;
	int		defsize;
}	t_vec;

int		vec_add(t_vec *arr, void *new_value);
void	init_vec(t_vec *arr, int defsize);
int		search_vec_(t_vec *arr, char *name);
int		search_vec(t_vec *arr, char *str, int size);
void	free_vec(t_vec *vec);
void	vec_rem(t_vec *vec, int pos);

#endif
