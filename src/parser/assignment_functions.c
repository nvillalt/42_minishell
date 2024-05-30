/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:31:36 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/30 18:08:46 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup_matrix(char **ret, char **aux, int j, int k)
{
	while (aux[k])
	{
		ret[j] = ft_strdup(aux[k]);
		j++;
		k++;
	}
}

int	init_process_cmd(t_parse **node)
{
	(*node)->cmd = ft_calloc(sizeof(char *), 2);
	if (!(*node)->cmd)
		return (0);
	return (1);
}

char	*init_quoteless_line(int num)
{
	char	*final;

	final = ft_calloc(sizeof(char), num + 1);
	if (!final)
		return (NULL);
	return (final);
}
