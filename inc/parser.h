#ifndef PARSER_H
# define PARSER_H

#include "structs.h"

#define	CMD 0
#define	PIPE 1
#define GREAT 2
#define APPEND 3
#define	HEREDOC 4
#define MINUS 5
#define BUILTIN 6

#define ECHO 1
#define PWD 2 
#define ENV 3 
#define UNSET 4 
#define CD 5 
#define EXIT 6 
#define EXPORT 7 



char	**get_path(char **env);

char	*clean_quotes(char *str);

int		is_whitespace(char c);
int		check_quotes(char *line, t_utils *utils);
int		whitespace_cmp(char *c);
int		initial_pipe(char *input, t_utils *utils);
int		check_redirections(char *input);

int     parse_tokens(t_utils *utils);

#endif