#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "inc/built-ins.h"
# include "inc/executor.h"
# include "inc/parser.h"
# include "inc/signals.h"
# include "inc/structs.h"
# include "inc/tokenizer.h"


/* ····· general utils & functions ····· */

// utils
char	**env_dup(char **env);
int		prompt_loop(t_utils *utils);

// free functions
char	**free_matrix(char **matrix);

#endif