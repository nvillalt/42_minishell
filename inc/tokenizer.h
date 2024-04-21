#ifndef TOKENIZER_H
# define TOKENIZER_H

t_token		*new_token(char **input);
void		add_token(t_token **list, t_token *new);

char		*trim_spaces(char *input);
void		clean_tokens(t_utils *utils, char *aux);

#endif