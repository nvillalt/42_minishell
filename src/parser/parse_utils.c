
#include "../../minishell.h"

// Devuelve un número para avanzar cuando cheque cosas 


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
