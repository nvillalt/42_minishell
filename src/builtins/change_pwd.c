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
	while (env[i] && ((ft_strncmp(env[i], var, varlen) != 0) || env_varlen(env[i]) != varlen))
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
		return (0);
	return (str + i + 1);
}

char	**change_old_pwd(char **env)
{
	char	*cwd;
	char	*temp_cwd;
	char	*temp;
	int		i;

	i = 0;
	while (env[i] && ((ft_strncmp(env[i], "OLDPWD", 6) != 0) || env_varlen(env[i]) != 6))
		i++;
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
			return (NULL);
	}
	temp = ft_strjoin("OLDPWD=", cwd);
	if (!temp)
	{
		free(cwd);
		free_matrix(env);
		perror("minishell");
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
	while (env[i] && ((ft_strncmp(env[i], "PWD", 3) != 0) || env_varlen(env[i]) != 3))
		i++;
	if (env[i] == NULL)
		return (env);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (env);
	temp = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!temp)
	{
		perror("minishell");
		free_matrix(env);
		return (NULL);
	}
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
	char	*ptr_current_pwd;
	char	*current_pwd;
	char	*new_pwd;
	char	*temp;
	int		i;

	i = 0;
	while (env[i] && ((ft_strncmp(env[i], "PWD", 3) != 0) || env_varlen(env[i]) != 3))
		i++;
	if (env[i] == NULL)
		return (env);
	ptr_current_pwd = ft_getenv(env, "PWD");
	if (!ptr_current_pwd)
		return (NULL);
	current_pwd = ft_strdup(ptr_current_pwd);
	if (!current_pwd)
		return (NULL);
	cmd = add_slash(cmd);
	if (!cmd)
	{
		free(current_pwd);
		return (NULL);
	}
	new_pwd = ft_strjoin(current_pwd, cmd);
	free(current_pwd);
	free(cmd);
	if (!new_pwd)
		return (NULL);
	temp = ft_strjoin("PWD=", new_pwd);
	free(new_pwd);
	if (!temp)
	{
		perror("minishell");
		free_matrix(env);
		return (NULL);
	}
	free(env[i]);
	env[i] = temp;
	return (env);
}
