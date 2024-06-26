/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:35:04 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/05 18:27:58 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_argc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	control_n(char **str, int i, int *n_flag)
{
	int	j;

	j = 2;
	while (str[i] && ft_strncmp(str[i], "-n", 2) == 0)
	{
		while (str[i][j] && str[i][j] == 'n')
		{
			j++;
		}
		if (str[i][j])
			break ;
		else
		{
			*n_flag = 0;
			i++;
			j = 2;
		}
	}
	return (i);
}

int	ft_echo(char **str)
{
	int	i;
	int	n_flag;
	int	argc;

	i = 1;
	n_flag = 1;
	if (!str[1])
	{
		printf("\n");
		return (0);
	}
	argc = count_argc(str);
	i = control_n(str, i, &n_flag);
	while (i < argc - 1)
	{
		printf("%s ", str[i]);
		i++;
	}
	if (str[i])
		printf("%s", str[i]);
	if (n_flag != 0)
		printf("\n");
	return (0);
}
