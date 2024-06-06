/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:23:46 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 16:20:41 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*search_for_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "HOME=", 5) != 0)
		i++;
	if (!env[i])
	{
		ft_putendl_fd ("minishell: cd: HOME not set", STDERR_FILENO);
		return (NULL);
	}
	if (!env[i][5])
		return (NULL);
	home = env[i] + 5;
	return (home);
}

static char	**change_to_directory(char **env, char *cmd)
{
	char	*cwd;

	env = change_old_pwd(env);
	if (!env)
		return (NULL);
	if (chdir(cmd) == -1)
		return (free_str_matrix_cderror(NULL, env, cmd));
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd(CD_ERR, STDERR_FILENO);
		ft_putstr_fd(CWD_ERR, STDERR_FILENO);
		ft_putendl_fd (FILE_ERR, STDERR_FILENO);
		env = change_pwd_error(env, cmd);
		if (!env)
			return (free(cwd), NULL);
	}
	else
	{
		env = change_pwd(env);
		if (!env)
			return (free(cwd), NULL);
	}
	free(cwd);
	return (env);
}

static char	**change_to_home(char **env)
{
	char	*home;
	char	*cwd;

	home = search_for_home(env);
	if (!home)
		return (free_matrix(env), NULL);
	env = change_old_pwd(env);
	if (!env)
		return (NULL);
	if (chdir(home) == -1)
		return (free_str_matrix_cderror(NULL, env, home));
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd(CD_ERR, STDERR_FILENO);
		ft_putstr_fd(CWD_ERR, STDERR_FILENO);
		ft_putendl_fd (FILE_ERR, STDERR_FILENO);
	}
	env = change_pwd(env);
	free(cwd);
	if (!env)
		return (NULL);
	return (env);
}

static int	return_success_cd(char **env, t_utils *utils)
{
	free_matrix(utils->env);
	utils->env = env;
	return (0);
}

int	ft_cd(t_utils *utils, char **cmd)
{
	t_cdvars	vars;

	init_cdvars(&vars, utils);
	if (!vars.env)
		return (perror("minishell"), 1);
	vars.i = count_matrix(cmd);
	if (vars.i == 1)
	{
		vars.env = change_to_home(vars.env);
		if (!vars.env)
		{
			if (!var_home_exist(utils->env))
				return (0);
			return (1);
		}
	}
	else if (vars.i == 2)
	{
		vars.env = change_to_directory(vars.env, cmd[1]);
		if (!vars.env)
			return (1);
	}
	else
		return (multiple_argc_error(vars.env));
	return (return_success_cd(vars.env, utils));
}
