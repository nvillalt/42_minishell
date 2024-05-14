#include "../../minishell.h"

static int	check_valid_symbol(char *str) // Implementar en parse, un if else con handle_quotes o esto, dependiendo
{
	int	i;

	i = 0;
	if (str[0] == '$' && str[1] == '?')
		return (1);
	while (str[i] == 34 || str[i] == 39)
		i++;
	if (str[i] == '$')
	{
		if (ft_isdigit(str[i + 1]))
			return (0);
		while (str[i])
		{
			if (str[i] == '-' || str[i] == '!' || str[i] == '?'
				|| str[i] == '\\' || str[i] == '/' ||str[i] == '('
				|| str[i] == ')')
				return (0);
			i++;
		}
	}
	return (1);
}

int	expansor(char *str, t_utils *utils) // Utils para acceder al env y 
{
	if (check_valid_symbol(str))
		return (1);	
}