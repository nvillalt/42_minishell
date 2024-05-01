#ifndef TOKENIZER_H
# define TOKENIZER_H

int			new_token(t_token **token);
int			add_token(t_token **list, t_token *new);
int			clear_token_list(t_token **token_list);
int			get_tokens(char	*aux, t_utils *utils);

char		*trim_spaces(char *input);
int			clean_tokens(t_utils *utils, char *aux);

#endif