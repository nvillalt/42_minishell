
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

int	ft_trimspaces(char **input)
{
	char	*cpy;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(*input);
	while(*input[i] == ' ' || (*input[i] >= 9 && *input[i] <= 13))
		i++;
	printf("%s\n%d\n", *input, i);
	cpy = ft_substr(*input, i, len - i + 1);
	if (!cpy)
		return (0);
	free(*input);
	*input = cpy;
	printf("%s\n", *input);
	return (1);
}