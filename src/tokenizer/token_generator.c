/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:55:21 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/09 19:02:46 by nvillalt         ###   ########.fr       */
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

int	get_substr(char *aux, int i)
{
	int	flag;

	flag = 0;
	while (aux[i])
	{
		if (!ft_strncmp(aux + i, "echo", 4))
			return (i + 4);
		if ((aux[i] == 34 && aux[i + 1] == 34)
			|| (aux[i + 1] == 39 && aux[i + 1] == 39)
			&& !ft_strncmp(aux + 2, "echo", 4))
			return (i + 2);
		if ((aux[i] == '<' && aux[i + 1] == '<')
			|| (aux[i] == '>' && aux[i + 1] == '>'))
			return (i + 2);
		if (aux[i] == '<' || aux[i] == '>')
			return (i + 1);
		if ((aux[i] == 34 || aux[i] == 39) && flag == 0)
			flag = aux[i];
		else if (aux[i] == flag)
			flag = 0;
		if (is_whitespace(aux[i]) && flag == 0)
			break ;
		i++;
	}
	return (i);
}

int	check_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i]) //TODO: REVISAR CON FRAN
	{
		if (check_redirections(str) == 2 || check_redirections(str) == 8)
		{
			ft_putendl_fd("syntax error near unexpected token `>'", 2);
			return (2);
		}
		else if (check_redirections(str) == 9 || check_redirections(str) == 4)
		{
			ft_putendl_fd("syntax error near unexpected token `newline'", 2);
			return (2);
		}
		else if (check_redirections(str) == 6)
		{
			ft_putendl_fd("syntax error near unexpected token `|'", 2);
			return (2);
		}
		i++;
	}
	return (1);
}

int	check_expand(char *temp)
{
	if (((temp[0] == 34 || temp[0] == 39) && temp[1] == '$')
		|| ((temp[0] == '$' && temp[1] == ' '))
		|| (temp[0] == '$' && temp[1] == '\0')
		|| (temp[0] == '$' && temp[1] == '='))
	{
		ft_putendl_fd("command not found: $", 2);
		return (0);
	}
	return (1);
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
		if (!new_token(&token) && utils->token_list != NULL)
			clear_token_list(&utils->token_list);
		temp = ft_substr(aux, i, (j - i));
		if (check_symbol(temp) == 1 && check_expand(temp) == 1)
			token->str = temp;
		if (!add_token(&utils->token_list, token) || token->str == NULL)
			return (free_tokens(&utils->token_list, temp, 1));
		while (is_whitespace(aux[j]))
			j++;
		i = j;
	}
	return (free_tokens(&utils->token_list, temp, 2));
}

//PRINTING NODES
	// t_token	*print;

	// print = utils->token_list;
	// printf("print: %s\n", print->str);
	// while (print->next != NULL)
	// {
	// 	print = print->next;
	// 	printf("print: %s\n", print->str);
	// }