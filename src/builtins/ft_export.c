/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:51:46 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 15:53:08 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_export_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		if (env[i] && ft_strncmp_varlen("_", env[i]) == 0)
			i++;
		if (!env[i])
			break ;
		j = 0;
		printf("declare -x ");
		while (env[i][j] && env[i][j] != '=')
		{
			printf("%c", env[i][j]);
			j++;
		}
		if (!env[i][j])
		{
			i++;
			printf("\n");
		}
		else
			print_no_value(env, &i, &j);
	}
}

static int	swap_lines(char **str1, char **str2)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup(*str1);
	if (!temp1)
		return (perror("minishell"), 0);
	temp2 = ft_strdup(*str2);
	if (!temp2)
	{
		free(temp1);
		perror("minishell");
		return (0);
	}
	free(*str1);
	free(*str2);
	*str1 = temp2;
	*str2 = temp1;
	return (1);
}

static int	sort_export_env(char **env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i + 1] != NULL)
	{
		j = 0;
		while (env[i][j] == env[i + 1][j])
			j++;
		if (env[i][j] > env[i + 1][j])
		{
			if (!swap_lines(&env[i], &env[i + 1]))
			{
				free_matrix(env);
				return (FUNC_FAILURE);
			}
			i = -1;
		}
		i++;
	}
	return (FUNC_SUCCESS);
}

static int	handle_export_single_argc(char **export_env)
{
	if (!sort_export_env(export_env))
		return (1);
	print_export_env(export_env);
	free_matrix(export_env);
	return (0);
}

int	ft_export(t_utils *utils, char **cmd)
{
	int		num;
	int		error_flag;
	char	**export_env;

	error_flag = 0;
	export_env = env_dup(utils->env);
	if (!export_env)
		return (1);
	num = count_matrix(cmd);
	if (!num)
		return (no_env_error());
	if (num == 1)
	{
		if (handle_export_single_argc(export_env) == 1)
			return (1);
	}
	else if (num > 1)
	{
		export_env = export_to_env(export_env, cmd, &error_flag);
		if (!export_env)
			return (1);
		free_matrix(utils->env);
		utils->env = export_env;
	}
	return (error_flag);
}
