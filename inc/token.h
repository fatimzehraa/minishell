/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:12:32 by fael-bou          #+#    #+#             */
/*   Updated: 2022/11/10 20:19:57 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "list.h"
# include "minishell.h"
# include "str.h"

# define CHAR_DQ '"'
# define CHAR_SQ '\''
# define CHAR_SDQ "'\""

enum e_token {
	TOKEN_WORD = 1,
	TOKEN_LITERAL = 1<<1,
	TOKEN_TEMPLATE = 1<<2,
	TOKEN_VAR = 1<<3,
	TOKEN_ASTERISK= 1<<4,
	TOKEN_RED_IN = 1<<5,
	TOKEN_RED_OUT = 1<<6,
	TOKEN_RED_APPEND = 1<<7,
	TOKEN_HEREDOC = 1<<8,
	TOKEN_PIPE = 1<<9,
	TOKEN_WHITESPACE = 1<<10,
	TOKEN_AND= 1<<11,
	TOKEN_OR= 1<<12,
	TOKEN_EOL = 1<<13,
	TOKEN_INVALID = 1<<14,
};

# define TOKEN_JOIN (0b11111)
# define TOKEN_RED (0b111100000)
# define TOKEN_LIST (0b11100000000000)

/*
 *
 * # define TOKEN_RED (TOKEN_RED_IN |
 * TOKEN_RED_OUT | TOKEN_RED_APPEND | TOKEN_HEREDOC)
 * # define TOKEN_JOIN (TOKEN_WORD |
 * TOKEN_LITERAL | TOKEN_TEMPLATE | TOKEN_VAR | TOKEN_ASTERISK)
 * #define TOKEN_LIST (TOKEN_AND | TOKEN_OR | TOKEN_EOL)
 *
*/

typedef struct s_token {
	enum e_token	type;
	t_str			str;
	int				has_space;
	int				len;
}	t_token;

void	exec_line(char *cmd, t_ctx *ctx);
t_list	*tokenizer(char	*command);
t_token	*tk(t_list *node);
void	free_token(void *ptr);
t_list	*new_token(char	*word);
int		string_len(char *cmd, char c);
int		is_var(char *cmd);
int		var_len(char *cmd);
int		word_len(char *cmd);
int		tk_fill(t_list *node, enum e_token type, char *dup_value, int len);

#endif // !TOKEN_H
