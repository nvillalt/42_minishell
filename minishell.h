/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:48:36 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 16:58:49 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

extern int	g_sigint;

// utils
char	**env_dup(char **env);
int		prompt_loop(t_utils *utils);
t_utils	init_utils(void);
int		ft_strncmp_varlen(char *cmd, char *env_line);

// free_functions
void	free_matrix(char **matrix);
void	free_utils(t_utils *utils);
void	free_lists(t_utils	*utils);
char	*free_puterror(char *str, char *str2, t_utils *utils, int status);
int		ft_puterror(char *cmd);
void	free_ptrs(void *ptr1, void *ptr2);
char	*updt_status_return(t_utils *utils, int status);
int		free_puterror_int(char *str, char *str2, t_utils *utils, int status);
void	exit_matrix_str(char *str, char **matrix, char *error, t_utils *utils);
void	exit_process_path(t_utils *utils, t_parse *process, int status);
int		change_status(t_utils *utils, int status);
void	exit_init_void(char **matrix);
int		free_matrix_return(char **matrix);
char	**free_str_matrix(char *str, char **matrix);

//printf double array
void	print_env(char **env);
int		count_matrix(char **cmds);

//init
char	**set_oldpwd(char **env);
int		update_shlvl(t_utils *utils);

#endif
