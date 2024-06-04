/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:14:24 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/04 17:30:43 by fmoran-m         ###   ########.fr       */
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
	char	*new_pwd;
	char	*temp;
	char	*current_pwd;
	char	*ptr_current_pwd;
	int		i;

	i = 0;
	ptr_current_pwd = ft_getenv(env, "PWD");
	if (!ptr_current_pwd)
		return (env);
	current_pwd = ft_strdup(ptr_current_pwd);
	if (!current_pwd)
		return (free_matrix(env), NULL);
	cmd = add_slash(cmd);
	if (!cmd)
		return (free_matrix(env), free(current_pwd), NULL);
	new_pwd = ft_strjoin(current_pwd, cmd);
	free_ptrs(current_pwd, cmd);
	if (!new_pwd)
		return (free_matrix(env), NULL);
	temp = ft_strjoin("PWD=", new_pwd);
	free(new_pwd);
	if (!temp)
		return (free_str_matrix(NULL, env));
	while(env[i] && ft_strncmp_varlen("PWD", env[i]))
		i++;
	free(env[i]);
	env[i] = temp;
	return (env);
}
