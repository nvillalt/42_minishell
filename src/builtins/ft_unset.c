/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:54:21 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 16:00:16 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	search_for_set_var(char **env, char *current_var, int *index_jump)
{
	int		var_len;

	var_len = ft_strlen(current_var);
	while (env[*index_jump]
		&& (ft_strncmp(env[*index_jump], current_var, var_len)
			|| var_len != env_varlen(env[*index_jump])))
		(*index_jump)++;
	if (!env[*index_jump])
		return (0);
	return (FUNC_SUCCESS);
}

static char	**search_for_var(char **env, char *current_var)
{
	int		index_jump;
	char	**new_env;

	index_jump = 0;
	if (!search_for_set_var(env, current_var, &index_jump))
		return (env_dup(env));
	new_env = unset_var_env(env, index_jump);
	if (!new_env)
		return (NULL);
	return (new_env);
}

int	ft_unset(t_utils *utils, char **cmd)
{
	int		index_var;
	char	**new_env;
	char	**old_env;

	if (!cmd[1])
		return (0);
	old_env = env_dup(utils->env);
	if (!old_env)
		return (perror("minishell"), 1);
	index_var = 1;
	new_env = NULL;
	while (cmd[index_var])
	{
		new_env = search_for_var(old_env, cmd[index_var]);
		if (!new_env)
			return (1);
		free_matrix(old_env);
		old_env = new_env;
		index_var++;
	}
	free_matrix(utils->env);
	utils->env = old_env;
	return (0);
}
