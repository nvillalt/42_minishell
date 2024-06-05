/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:21:06 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/04 19:07:17 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_export_format(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
		return (0);
	i++;
	while (cmd[i] && cmd[i] != '=' && ft_isalnum(cmd[i]))
		i++;
	if (cmd[i] == '+' && cmd[i + 1] == '=')
		return (2);
	if (cmd[i] == 0 || cmd[i] == '=')
		return (1);
	else
		return (0);
}

char	**add_to_env(char **env, char *cmd, int *error_flag)
{
	int		export_format;
	char	*new_cmd;

	export_format = is_export_format(cmd);
	if (!export_format)
	{
		ft_putstr_fd ("bash: export: \'", STDERR_FILENO);
		ft_putstr_fd (cmd, STDERR_FILENO);
		ft_putendl_fd ("\': not a valid identifier", STDERR_FILENO);
		*error_flag = 1;
		return (env);
	}
	if (export_format == 2)
	{
		new_cmd = delete_plus(cmd);
		if (!new_cmd)
			return (NULL);
		cmd = new_cmd;
	}
	env = create_new_env(env, cmd);
	if (!env)
		return (NULL);
	return (env);
}

int	get_cmd_flag(char **env, char *cmd, int cmd_len, int plus_flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if ((ft_strncmp(env[i], cmd, cmd_len) == 0) && j == cmd_len)
		{
			if (plus_flag == 1)
				return (2);
			else if (env[i][j] == '=' || !env[i][j])
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

char	**join_var(char **env, char *cmd)
{
	int		i;
	char	*temp;
	int		var_len;
	char	*cmd_value;

	var_len = 0;
	while (cmd[var_len] && cmd[var_len] != '+')
		var_len++;
	if (!cmd[var_len])
		return (env);
	i = 0;
	while (ft_strncmp(env[i], cmd, var_len) != 0
		|| var_len != env_varlen(env[i]))
		i++;
	var_len = var_len + 2;
	if (!cmd[var_len])
		return (env);
	temp = ft_strjoin(env[i], cmd + var_len);
	if (!temp)
		return (free_matrix(env), perror("minishell"), NULL);
	free(env[i]);
	env[i] = temp;
	return (env);
}

void	print_no_value(char **env, int *i, int *j)
{
	printf("%c", env[*i][*j]);
	(*j)++;
	printf("%c", '\"');
	while (env[*i][*j])
	{
		printf("%c", env[*i][*j]);
		(*j)++;
	}
	printf("%c", '\"');
	printf("\n");
	(*i)++;
}
