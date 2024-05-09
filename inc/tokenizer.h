#ifndef TOKENIZER_H
# define TOKENIZER_H

// token_list.c
int			new_token(t_token **token);
int			add_token(t_token **list, t_token *new);
int			clear_token_list(t_token **token_list);
int	        free_tokens(t_token **token_list, char *temp, int n);
int			get_tokens(char	*aux, t_utils *utils);

// token_generator.c
char		*trim_spaces(char *input);

#endif