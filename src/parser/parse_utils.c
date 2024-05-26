/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:23:21 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/26 20:32:35 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_token(char c)
{
	if (!c)
		return (0);
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	is_whitespace(char c)
{
	if (c == '\0')
		return (0);
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

int	check_quotes(char *line, t_utils *utils)
{
	int	flag;
	int	i;

	if (*line == '\0' || line == NULL)
		return (-1);
	flag = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == 34 || line[i] == 39) && flag == 0)
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

int	assert_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			return (1);
		i++;
	}
	return (0);
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
	else if (input[len - 1] == '>' || input[len - 1] == '<')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd("syntax error near end of line `newline'", 2);
		return (0);
	}
	return (1);
}
