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
	char	**env; // Para el env duplicado
	char	*prompt; // Guardar el string que entre desde readline

} t_utils;

typedef struct s_token
{
	t_macro			token;
	char			*str;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

#endif