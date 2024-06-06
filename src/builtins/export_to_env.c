/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_to_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:15:16 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 17:16:33 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**create_new_env(char **env, char *cmd)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc(count_matrix(env) + 2, sizeof(char *));
	if (!new_env)
		return (free_matrix(env), perror("minishell"), NULL);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_matrix(env), free_matrix(new_env),
				perror("minishell"), NULL);
		i++;
	}
	new_env[i] = ft_strdup(cmd);
	if (!new_env[i])
		return (free_matrix(env), free_matrix(new_env),
			perror("minishell"), NULL);
	free_matrix(env);
	return (new_env);
}

int	cmd_on_env(char **env, char *cmd)
{
	int	i;
	int	cmd_len;
	int	plus_flag;

	i = 0;
	cmd_len = 0;
	plus_flag = 0;
	if (*cmd == '=')
	{
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (-1);
	}
	while (cmd[cmd_len] && cmd[cmd_len] != '=')
		cmd_len++;
	if (cmd[cmd_len] == '=' && cmd[cmd_len - 1] == '+' && cmd_len > 1)
	{
		cmd_len--;
		plus_flag = 1;
	}
	return (get_cmd_flag(env, cmd, cmd_len, plus_flag));
}

char	**change_var(char **env, char *cmd)
{
	int		i;
	char	*temp;
	int		var_len;

	var_len = 0;
	while (cmd[var_len] && cmd[var_len] != '=')
		var_len++;
	if (!cmd[var_len])
		return (env);
	i = 0;
	while (ft_strncmp(env[i], cmd, var_len) != 0
		|| var_len != env_varlen(env[i]))
		i++;
	temp = ft_strdup(cmd);
	if (!temp)
		return (free_matrix(env), perror("minishell"), NULL);
	free(env[i]);
	env[i] = temp;
	return (env);
}

char	**handle_newvar(char **env, char *cmd, int setvar, int *error_flag)
{
	if (setvar == 1)
	{
		env = change_var(env, cmd);
		if (!env)
			return (NULL);
	}
	else if (setvar == 2)
	{
		env = join_var(env, cmd);
		if (!env)
			return (NULL);
	}
	else
	{
		env = add_to_env(env, cmd, error_flag);
		if (!env)
			return (NULL);
	}
	return (env);
}

char	**export_to_env(char **env, char **cmd, int *error_flag)
{
	int	i;
	int	setvar;

	i = 1;
	while (cmd[i])
	{
		if (!cmd[i][0])
		{
			ft_putendl_fd(QUOTES_ERR, STDERR_FILENO);
			*error_flag = 1;
		}
		else
		{
			setvar = cmd_on_env(env, cmd[i]);
			if (setvar == -1)
				return (free_matrix(env), NULL);
			env = handle_newvar(env, cmd[i], setvar, error_flag);
			if (!env)
				return (NULL);
		}
		i++;
	}
	return (env);
}
