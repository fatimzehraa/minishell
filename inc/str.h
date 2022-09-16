#ifndef STR_H
#define STR_H

typedef struct s_str
{
	char *val;
	int size;
	int cap;
}	t_str;

int	ft_strlen(char *s);
int	has_chars(char c, char *chrs);
int	is_space(char c);
int	is_alphanum(char c);
int	is_special(char *s);
int	ft_strncmp(char *s1, char *s2, int n);
void	ft_strncpy(char *dest, char *src, unsigned int size);
char	*ft_strndup(char *src, int len);

#endif
