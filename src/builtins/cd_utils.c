/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:13:36 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/04 19:55:25 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_env_index(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp_varlen(var, env[i]))
		i++;
	return (i);
}

int	env_varlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**free_str_matrix_cderror(char *str, char **matrix, char *perror_msg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(perror_msg);
	if (str)
		free(str);
	if (matrix)
		free_matrix(matrix);
	return (NULL);
}

int	multiple_argc_error(char **env)
{
	ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
	if (env)
		free_matrix(env);
	return (1);
}

int	var_home_exist(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "HOME=", 5) != 0)
		i++;
	if (!env[i])
		return (1);
	if (!env[i][5])
		return (0);
	return (1);
}