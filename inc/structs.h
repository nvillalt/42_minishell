/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:24:02 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 16:14:06 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_redir
{
	char			*doc;
	char			*heredoc_file;
	int				heredoc_flag;
	int				redir_type;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_parse
{
	char			**cmd;
	int				built_in;
	t_redir			*redirec;
	t_redir			*redirec_head;
	struct s_parse	*next;
}	t_parse;

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
	int				expand;
	int				dbl_quote;
}	t_token;

typedef struct s_utils
{
	char	**path;
	char	**env;
	t_parse	*process;
	t_token	*token_list;
	int		status;
	pid_t	*pid_array;
	int		main_pipe[2];
	int		aux_pipe[2];
	int		process_list_len;
	int		builtin_counter;
	int		parent_builtin;
	int		saved_stdin;
	int		saved_stdout;
}	t_utils;

struct s_pwderror
{
	char	*new_pwd;
	char	*temp;
	char	*current_pwd;
	char	*ptr_current_pwd;
	int		i;
};

typedef struct s_cdvars
{
	int		i;
	char	**env;
}	t_cdvars;
#endif