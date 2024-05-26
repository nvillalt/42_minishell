/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/26 16:30:11 by nvillalt         ###   ########.fr       */
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