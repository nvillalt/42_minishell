
#include "../../minishell.h"

// Devuelve un número para avanzar cuando cheque cosas 
int	check_quotes(char *str)
{
	int	i;
	int	sgl;
	int	dbl;

	i = 0;
	sgl = 0;
	dbl = 0;
	while (str[i])
	{
		if (str[i] == 39)
			sgl++;
		if (str[i] == 34)
			dbl++;
		i++;
	}
	if (sgl % 2 == 0 && dbl % 2 == 0)
		return (1);
	return (0);
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

int	ft_trimspaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
		i++;
	return (i);
}

int	check_redirections(t_utils *utils, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
			error_message(utils);
		if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '|')
			error_message(utils);
		if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
			error_message(utils);
		if (input[i] == '|' && input[i + 1] == '<')
			error_message(utils);
		if (input[i] == '<' && input[i + 1] == '|')
			error_message(utils);
		if (input[i] == '|' && input[i + 1] == '|')
			error_message(utils);
		if (input[i] == '&' && input[i + 1] == '&')
			error_message(utils);
		i++;
	}
	return (1);
}
