#ifndef TOKENIZER_H
# define TOKENIZER_H

char		*new_token(t_token **token, char **input);
void		add_token(t_token **list, t_token *new);
void		parse_tokens(t_utils *utils, t_token **token_list);
void		clear_token_list(t_token **token_list);

char		*trim_spaces(char *input);
int			clean_tokens(t_utils *utils, char *aux);

#endif