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
}	t_utils;

#endif