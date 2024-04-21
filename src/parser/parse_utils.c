
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
	if (input[i])
		return (i);
	return (0);
}

int		check_quotes(char *line)
{
	int	flag;
	int	i;

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
		return (0);
	return (1);
}

int	initial_pipe(char *input)
{
	int	i;
	int	len;

	i = whitespace_cmp(input);
	len = ft_strlen(input);
	while (is_whitespace(input[len - 1]))
		len--;
	if (input[len - 1] == '|' || input[i] == '|' || input[len - 1] == '>'
		|| (input[len - 1] == '>' && input[len - 2] == '>'))
		return (0);
	return (1);
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
