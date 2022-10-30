#include "cmd.h"
#include "list.h"
#include "minishell.h"
#include "token.h"

int is_special_token(t_token *token) {
  if (token->type == TOKEN_PIPE || token->type == TOKEN_AND ||
      token->type == TOKEN_OR)
    //		|| token->type == TOKEN_EOL)
    return (1);
  return (0);
}

int check_if_followed(t_list *tokens) {
  return (is_special_token(tk(tokens)) &&
		  (is_special_token(tk(tokens->next)) || tk(tokens->next)->type == TOKEN_EOL));
}

int check_redirections(t_list *tokens) {
  return ((tk(tokens)->type & TOKEN_RED) &&
		  (is_special_token(tk(tokens->next)) || tk(tokens->next)->type == TOKEN_EOL));
}

int check_syntax(t_list *tokens) {
  if (is_special_token(tk(tokens)))
    return (0);
  tokens = tokens->next;
  if (tk(tokens)->type == TOKEN_EOL)
    return (1);
  while (tk(tokens)->type != TOKEN_EOL) {
    if (check_if_followed(tokens))
      return (0);
    else if (check_redirections(tokens))
      return (0);
    tokens = tokens->next;
  }
  return (1);
}
