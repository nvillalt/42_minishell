/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:14:24 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 15:56:30 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(char **env, char *var)
{
	int		i;
	int		varlen;
	char	*str;

	i = 0;
	varlen = env_varlen(var);
	while (env[i] && ft_strncmp_varlen(var, env[i]))
		i++;
	if (!env[i])
		return (NULL);
	str = env[i];
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	if (!str[i + 1])
		return (NULL);
	return (str + i + 1);
}

char	**change_old_pwd(char **env)
{
	char	*cwd;
	char	*temp_cwd;
	char	*temp;
	int		i;

	i = get_env_index(env, "OLDPWD");
	if (env[i] == NULL)
		return (env);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		temp_cwd = ft_getenv(env, "OLDPWD");
		if (!temp_cwd)
			return (env);
		cwd = ft_strdup(temp_cwd);
		if (!cwd)
			return (free_matrix(env), perror("minishell"), NULL);
	}
	temp = ft_strjoin("OLDPWD=", cwd);
	if (!temp)
		return (free_str_matrix(cwd, env));
	free_ptrs(cwd, env[i]);
	env[i] = temp;
	return (env);
}

char	**change_pwd(char **env)
{
	char	*cwd;
	char	*temp;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp_varlen("PWD", env[i]))
		i++;
	if (env[i] == NULL)
		return (env);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (env);
	temp = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!temp)
		return (free_str_matrix(NULL, env));
	free(env[i]);
	env[i] = temp;
	return (env);
}

static char	*add_slash(char *current_pwd)
{
	int	i;

	i = 0;
	if (current_pwd[i] != '/')
	{
		current_pwd = ft_strjoin("/", current_pwd);
		if (!current_pwd)
			return (NULL);
	}
	return (current_pwd);
}

char	**change_pwd_error(char **env, char *cmd)
{
	struct s_pwderror	pwd;

	pwd.i = 0;
	pwd.ptr_current_pwd = ft_getenv(env, "PWD");
	if (!pwd.ptr_current_pwd)
		return (env);
	pwd.current_pwd = ft_strdup(pwd.ptr_current_pwd);
	if (!pwd.current_pwd)
		return (free_matrix(env), NULL);
	cmd = add_slash(cmd);
	if (!cmd)
		return (free_matrix(env), free(pwd.current_pwd), NULL);
	pwd.new_pwd = ft_strjoin(pwd.current_pwd, cmd);
	free_ptrs(pwd.current_pwd, cmd);
	if (!pwd.new_pwd)
		return (free_matrix(env), NULL);
	pwd.temp = ft_strjoin("PWD=", pwd.new_pwd);
	free(pwd.new_pwd);
	if (!pwd.temp)
		return (free_str_matrix(NULL, env));
	while (env[pwd.i] && ft_strncmp_varlen("PWD", env[pwd.i]))
		pwd.i++;
	free(env[pwd.i]);
	env[pwd.i] = pwd.temp;
	return (env);
}
