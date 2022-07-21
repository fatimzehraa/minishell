#ifndef STR_H
#define STR_H

int	ft_strlen(char *s);
int	has_chars(char c, char *chrs);
int	is_space(char c);
int	is_alphanum(char c);
int	is_special(char *s);
int	ft_strncmp(char *s1, char *s2, int n);
int	ft_putstr(int fd, char *s);
void	ft_strncpy(char *dest, char *src, unsigned int size);
char	*ft_strjoin(char *s1, char *s2, int s2_len);
char	*ft_strndup(char *src, int len);
int	ft_append(char *dest, char *src, int len);
int	til_set(char *str, char *set, int n);
char	*ft_strchr(char *s, int c);
int	is_space(char a);
int	ft_isalpha(int c);

#endif
