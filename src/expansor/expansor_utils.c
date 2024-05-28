/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/28 15:14:19 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_expand	*init_exp(t_utils *utils)
{
	t_expand	*exp_utils;

	exp_utils = ft_calloc(sizeof(t_expand), 1);
	if (!exp_utils)
		return (NULL);
	exp_utils->status = utils->status;
	exp_utils->env = utils->env;
	return (exp_utils);
}

char	*ft_strjoin_expand(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	k = 0;
	ptr = (char *)ft_calloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[k])
	{
		ptr[i] = s2[k];
		i++;
		k++;
	}
	free(s1);
	return (ptr);
}