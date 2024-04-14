#ifndef TOKENIZER_H
# define TOKENIZER_H

int			word_to_token(t_utils *utils, char *input);

t_token		*new_token(char *input, int i, int j);
void		add_token(t_token **list, t_token *new);

#endif