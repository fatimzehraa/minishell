#ifndef STR_H
#define STR_H

typedef struct s_str
{
	char *val;
	int size;
	int cap;
}	t_str;

int		ft_strlen(char *s);
int		has_chars(char c, char *chrs);
int		is_space(char c);
int		is_alphanum(char c);
int		is_special(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_putstr(int fd, char *s);
void	ft_strncpy(char *dest, char *src, unsigned int size);
char	*ft_strjoin(char *s1, char *s2, int s2_len);
char	*ft_strndup(char *src, int len);
int		ft_append(char *dest, char *src, int len);
int		til_set(char *str, char *set, int n);
char	*ft_strchr(char *s, int c);
int	is_space(char c);
int	ft_isalpha(int c);
int	ft_isnum(int c);

int str_mk(t_str *str, char *s);
int str_push(t_str *s1, t_str *s2);
int str_same(t_str *s1, t_str *s2, int s2_size);
int str_clone(t_str *dest, t_str *src);
#endif
