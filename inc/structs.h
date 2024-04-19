#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_macro
{
	int	MORE;
	int	MORE_X2;
	int	LESS;
	int	LESS_X2;
	int	PIPE;
} t_macro;
typedef struct s_utils
{
	char	**path; // Guardar los comandos de path por si hay que hacer rutas luego
	char	**env; // Para el env duplicado
	char	*prompt; // Guardar el string que entre desde readline
	struct	s_parse *cmds;
} t_utils;
typedef struct s_token
{
	t_macro			token;
	char			*str;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;
typedef struct	s_redir
{
	char			*doc;
	int				redir_type; //tipo de redireccion
	int				fd;
	struct s_redir	*next;
}	t_redir;
typedef	struct s_parse
{
	char			**cmd;
	int				built_in; //built-in - cmd
	t_redir			*redirec;
	struct s_parse	*next;
}	t_parse;
#endif