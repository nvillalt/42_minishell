/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/13 23:08:28 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*trim_spaces(char *input)
{
	char	*str;
	int		i;
	int		len;

	i = whitespace_cmp(input);
	len = ft_strlen(input);
	if (*input == '\0')
		return (NULL);
	if (i == len)
		return (NULL);
	while (is_whitespace(input[len - 1]))
		len--;
	str = ft_substr(input, i, len - i);
	return (str);
}
static int	check_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i]) //TODO: REVISAR CON FRAN LOS ERRORES
	{
		if (check_redirections(str) == 2 || check_redirections(str) == 8)
		{
			ft_putendl_fd("syntax error near unexpected token `>'", 2);
			return (-1);
		}
		else if (check_redirections(str) == 9 || check_redirections(str) == 4)
		{
			ft_putendl_fd("syntax error near unexpected token `newline'", 2);
			return (-1);
		}
		else if (check_redirections(str) == 6)
		{
			ft_putendl_fd("syntax error near unexpected token `|'", 2);
			return (-1);
		}
		i++;
	}
	return (1);
}

static int	check_expand(char *temp)
{
	if (((temp[0] == '$' && temp[1] == ' '))
		|| (temp[0] == '$' && temp[1] == '\0')
		|| (temp[0] == '$' && temp[1] == '='))
	{
		ft_putendl_fd("command not found: $", 2);
		return (-1);
	}
	return (1);
}

static int	get_substr(char *aux, int i)
{
	int	flag;

	flag = 0;
	while (aux[i])
	{
		if ((aux[i] == 34 || aux[i] == 39) && flag == 0)
		{
			flag = aux[i];
			i++;
			while (aux[i] != flag)
				i++;
			flag = 0;
		}
		if ((!flag && (is_token(aux[i]) || is_whitespace(aux[i]))))
		{
			while (is_token(aux[i]))
				i++;
			break ;
		}
		else if (!flag && is_token(aux[i + 1]))
			return (i + 1);
		i++;
	}
	return (i);
}

int	get_tokens(char	*aux, t_utils *utils)
{
	t_token	*token;
	char	*temp;
	int		i;
	int		j;

	token = NULL;
	j = 0;
	if (aux == NULL)
		return (0);
	i = 0;
	while (aux[i])
	{
		j = get_substr(aux, i);
		if ((!new_token(&token) && utils->token_list != NULL) || j == -1)
			return (clear_token_list(&utils->token_list));
		temp = ft_substr(aux, i, (j - i));
		if (check_symbol(temp) == 1 && check_expand(temp) == 1)
			token->str = temp;
		if (!add_token(&utils->token_list, token) || token->str == NULL)
			return (free_tokens(&utils->token_list, temp, 1));
		while (is_whitespace(aux[j]))
			j++;
		i = j;
	}
	return (0);
}
