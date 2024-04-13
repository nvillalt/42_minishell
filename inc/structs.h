#ifndef STRUCTS_H
# define STRUCTS_H


typedef struct s_token
{
	int				flag;
	char			*str;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;


typedef struct	s_redir
{
	char			*doc; // documento / EOF que va con la redirección
	int				flag; // tipo de redirección
	struct s_redir	*next;
	struct s_redir	*prev;
} t_redir;

typedef struct s_parse
{
	char			**cmd;
	char			*builtin;
	t_redir			*redir;
	struct s_parse	*next;
	struct s_parse	*prev;
} t_parse;

typedef struct s_utils
{
	char	**path; // Guardar los comandos de path por si hay que hacer rutas luego
	char	**env; // Para el env duplicado
	char	*prompt; // Guardar el string que entre desde readline
	t_token	*token;
	t_parse	*parse;

} t_utils;

#endif