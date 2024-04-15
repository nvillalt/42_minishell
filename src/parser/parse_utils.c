
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

int		check_quotes(char *line)
{
	int	count;
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == 34 || line[i] == 39) && flag ==  0)
		{
			flag = line[i];
			count++;
		}
		if (line[i] == flag)
		{
			flag = 0;
			count++;
		}
		i++;
	}
	if (!flag && (count % 2 == 0))
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
