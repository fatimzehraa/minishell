#ifndef TOKEN_H
#define TOKEN_H

# include"list.h"
# include"minishell.h"

# define VAR_CHAR "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789_"
enum e_token {
	TOKEN_WORD = 1,
	TOKEN_LITERAL = 1<<1,
	TOKEN_TEMPLATE = 1<<2,
	TOKEN_VAR = 1<<3,
	TOKEN_RED_IN = 1<<4,
	TOKEN_RED_OUT = 1<<5,
	TOKEN_RED_APPEND = 1<<6,
	TOKEN_HEREDOC = 1<<7,
	TOKEN_PIPE = 1<<8,
	TOKEN_WHITESPACE = 1<<9,
	TOKEN_EOL = 1<<10,
};

typedef struct s_token {
	enum e_token	type;
	char			*value;
	int				len;
} t_token;

void	exec_line(char *cmd, t_ctx *ctx);
t_list	*tokenizer(char	*command);
t_token	*tk(t_list *node);
void	free_token(void *ptr);
t_list	*new_token(char	*word);
int	string_len(char *cmd, char c);
int	is_var(char *cmd);
int	var_len(char *cmd);
int word_len(char *cmd);

#endif // !TOKEN_H
