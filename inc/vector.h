#ifndef VECTOR_H
#define VECTOR_H

typedef struct s_vec {
	void	**content;
	int		len;
	int		size;
	int		defsize;
}	t_vec;

int		vec_add(t_vec *arr, void *new_value);
void	init_vec(t_vec *arr, int defsize);
int		search_vec(t_vec *arr, t_str *str);
void	free_vec(t_vec *vec);
void	vec_rem(t_vec *vec, int pos);

#endif
