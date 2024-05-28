#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h> //Se puede usar?
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <sys/ioctl.h>
# include "inc/structs.h"
# include "libft/libft.h"
# include "inc/builtins.h"
# include "inc/executor.h"
# include "inc/parser.h"
# include "inc/signals.h"
# include "inc/tokenizer.h"
# include "inc/expansor.h"
/* ····· general utils & functions ····· */

extern int	g_sigint;

// utils
char	**env_dup(char **env);
int		prompt_loop(t_utils *utils);
t_utils	init_utils(void);

// error_management
int		error_message(t_utils *utils);

// free_functions
void 	free_matrix(char **matrix);
void	free_utils(t_utils *utils);
void	free_lists(t_utils	*utils);
//printf double array
void	print_env(char **env);
int		ft_puterror(char *cmd);
int     count_matrix(char **cmds);
#endif
