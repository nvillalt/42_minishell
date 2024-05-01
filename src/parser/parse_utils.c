
#include "../../minishell.h"

int	is_whitespace(char	c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	whitespace_cmp(char *input)
{
	int	i;

	i = 0;
	while (input[i] && is_whitespace(input[i]))
		i++;
	return (i);
}

int		check_quotes(char *line, t_utils *utils)
{
	int	flag;
	int	i;

	if (*line == '\0' || line == NULL)
		return (-1);
	flag = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == 34 || line[i] == 39) && flag ==  0)
			flag = line[i];
		else if (line[i] == flag)
			flag = 0;
		i++;
	}
	if (flag)
	{
		ft_putstr_fd("minishell: syntax error `unclosed quotes'\n", 2);
		return (0);
	}
	return (1);
}

int	initial_pipe(char *input, t_utils *utils)
{
	int	i;
	int	len;

	if (*input == '\0' || input == NULL)
		return (-1);
	i = whitespace_cmp(input);
	len = ft_strlen(input);
	if (i == len)
		return (-1);
	while (is_whitespace(input[len - 1]))
		len--;
	if (input[len - 1] == '|' || input[i] == '|')
	{
		ft_putendl_fd("minishell: syntax error near end of line `|'", 2);
		return (0);
	}
	return (1);
}

int	check_redirections(char *input)
{
	if (input[0] == '>' && input[1] == '>' && input[2] == '>')
		return (2);
	if (input[0] == '>' && input[1] == '>' && input[2] == '|')
		return (3);
	if (input[0] == '<' && input[1] == '<' && input[2] == '<')
		return (4);
	if (input[0] == '|' && input[1] == '<')
		return (5);
	if (input[0] == '<' && input[1] == '|')
		return (6);
	if (input[0] == '|' && input[1] == '|')
		return (7);
	if (input[0] == '>' && input[1] == '<')
		return (8);
	if (input[0] == '<' && input[1] == '>')
		return (9);
	return (1);
}

// Ojo ls >| hola se entiende como ls >hola y ya, 
// Pero ls |> hola se entiende como ls | "" >hola
