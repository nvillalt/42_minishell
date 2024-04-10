
#include "../../minishell.h"

// Devuelve un número para avanzar cuando cheque cosas 
int	check_quotes(char *line)
{
	// Contar las quotes (single y double + avanzar en la string)
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{

		i++;
	}
	return (1);
}

int	strcmp_spaces(char *str)
{
	int	i;

	i = 0;
	while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (1);
}

char	*ft_trimspaces(char *input)
{
	//TODO: revisar esta función para que gestione caracteres no imprimibles
	char	*cpy;
	int		i;

	i = 0;
	cpy = ft_strtrim(input, " ");
	free(input);
	return (cpy);
}