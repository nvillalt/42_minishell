
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
	{
		ft_putstr_fd("Error: unclosed quotes", 2);
		return (0);
	}
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
	if (input[len - 1] == '|' || input[i] == '|')
	{
		ft_putstr_fd("error. unexpected '|'.", 2);
		return (0);
	}
	if ((input[len - 1] == '>' && input[len - 2] == '<') || input[len - 1] == '<' && input[len - 2 == '>']
		|| input[len - 1] == '>' && input[len - 2] == '>' && input[len - 3] == '>')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'", 2);
		return (0);
	}
	if (input[len - 1] == '>' || (input[len - 1] == '>' && input[len - 2] == '>')
		|| input[len - 1] == '<' || (input[len - 1] == '<' && input[len - 2] == '<'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'", 2);
		return (0);
	}
	return (1);
}

int	check_redirections(char *input)
{
	if (input[0] == '>' && input[1] == '>' && input[2] == '>')
		return (0);
	if (input[0] == '>' && input[1] == '>' && input[2] == '|')
		return (0);
	if (input[0] == '<' && input[1] == '<' && input[2] == '<')
		return (0);
	if (input[0] == '|' && input[1] == '<')
		return (0);
	if (input[0] == '<' && input[1] == '|')
		return (0);
	if (input[0] == '|' && input[1] == '|')
		return (0);
	if (input[0] == '>' && input[1] == '<')
		return (0);
	if (input[0] == '<' && input[1] == '>')
		return (0);
	return (1);
}
