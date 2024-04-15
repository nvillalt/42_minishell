#ifndef TOKENIZER_H
# define TOKENIZER_H

t_token		*new_token(char *input, int i, int j);
void		add_token(t_token **list, t_token *new);

#endif