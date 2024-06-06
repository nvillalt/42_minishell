/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 15:42:35 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_dollar(char *str, int j, char **aux, t_expand *exp_utils)
{
	return (get_mid(str, j, aux, exp_utils));
}

int	process_non_dollar(char *str, int i, int j, char **aux)
{
	while (str[j] != '\0' && str[j] != '$')
		j++;
	*aux = ft_substr(str, i, j - i);
	return (j);
}

void	join_aux_to_tmp(char **tmp, char *aux)
{
	char	*new_tmp;

	if (!(*tmp))
		*tmp = ft_strdup(aux);
	else
	{
		new_tmp = ft_strjoin_expand(*tmp, aux);
		*tmp = new_tmp;
	}
}
