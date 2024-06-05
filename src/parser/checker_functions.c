/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:23:47 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/05 20:18:10 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

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

int	validate_redir(char *s)
{
	if ((!ft_strncmp(s, "<", 1) && ft_strlen(s) == ft_strlen("<"))
		|| (!ft_strncmp(s, "<<", 2) && ft_strlen(s) == ft_strlen("<<"))
		|| (!ft_strncmp(s, ">|", 2) && ft_strlen(s) == ft_strlen(">|"))
		|| (!ft_strncmp(s, "|>", 2) && ft_strlen(s) == ft_strlen("|>"))
		|| (!ft_strncmp(s, ">", 1) && ft_strlen(s) == ft_strlen(">"))
		|| (!ft_strncmp(s, ">>", 2) && ft_strlen(s) == ft_strlen(">>")))
		return (1);
	return (0);
}
