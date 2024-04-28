#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_redir
{
	char			*doc; // NULL
	char			*heredoc_file; //NULL
	int				redir_type; // a -1
	int				fd; // -1
	struct s_redir	*next;
}	t_redir;

typedef	struct s_parse
{
	char			**cmd;
	int				built_in; //built-in - cmd
	t_redir			*redirec;
	t_redir			*redirec_head; // a NULL, guarda la cabecera de la lista y no se toca
	struct s_parse	*next;
}	t_parse;


typedef struct s_token
{
	char						*str;
	struct s_token	*next;
} t_token;

typedef struct s_utils
{
	char	**path; // Guardar los comandos de path por si hay que hacer rutas luego
	char	**env; // Para el env duplicado
	t_parse	*process;
	int		status; // a 0
	pid_t	*pid_array; // A NULL
} t_utils;

#endif