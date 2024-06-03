/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:23:20 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 15:23:30 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*delete_plus(char *cmd)
{
	int		new_cmd_len;
	char	*new_cmd;
	int		j;
	int		i;

	i = 0;
	j = 0;
	new_cmd_len = ft_strlen(cmd) - 1;
	new_cmd = ft_calloc(new_cmd_len + 1, sizeof(char));
	if (!new_cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '+')
			i++;
		new_cmd[j] = cmd[i];
		j++;
		i++;
	}
	return (new_cmd);
}
