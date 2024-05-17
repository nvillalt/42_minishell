#include "../../minishell.h"

int	env_varlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*ft_getenv(char **env, char *var)
{
	int		i;
	int		varlen;
	char	*str;

	i = 0;
	varlen = env_varlen(var);
	while (env[i] && (ft_strncmp(env[i], var, varlen) != 0) && env_varlen(env[i]) != varlen)
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
	str = ft_strdup(str + i + 1);
	if (!str)
		return (NULL);
	return (str);
}

char	**change_old_pwd(char **env)
{
	char	*cwd;
	char	*temp;
	int		i;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], "OLDPWD", 6) != 0) && env_varlen(env[i]) != 6)
		i++;
	if (env[i] == NULL)
		return (env);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_getenv(env, "PWD");
		if (!cwd)
			return (env);
	}
	temp = ft_strjoin("OLDPWD=", cwd);
	if (!temp)
	{
		free(cwd);
		perror("minishell");
		free_matrix(env);
		return (NULL);
	}
	free(cwd);
	free(env[i]);
	env[i] = temp;
	return (env);
}

char	**change_pwd(char **env)
{
	char	*cwd;
	char	*temp;
	int		i;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], "PWD", 3) != 0) && env_varlen(env[i]) != 6)
		i++;
	if (env[i] == NULL)
		return (env);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (env);
	temp = ft_strjoin("PWD=", cwd);
	if (!temp)
	{
		free(cwd);
		perror("minishell");
		free_matrix(env);
		return (NULL);
	}
	free(cwd);
	free(env[i]);
	env[i] = temp;
	return (env);
}
