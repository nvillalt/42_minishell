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


char	**get_path(char **env);

int		check_quotes(char *line);
int		strcmp_spaces(char *str);
int		ft_trimspaces(char *input);
int		check_redirections(t_utils *utils, char *input);

#endif