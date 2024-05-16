#include "../../minishell.h"

char	**change_old_pwd(char **env)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "OLDPWD", 6) != 0)
		i++;
	if (env[i] == NULL)
		return (env);
	temp = getcwd(NULL, 0);
	if (!temp)
	{
		perror("minishell");
		free_matrix(env);
		return (NULL);
	}
	temp2 = ft_strjoin("OLDPWD=", temp);
	if (!temp2)
	{
		free(temp);
		perror("minishell");
		free_matrix(env);
		return (NULL);
	}
	free(temp);
	free(env[i]);
	env[i] = temp2;
	return (env);
}

char	**change_pwd(char **env)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD", 3) != 0)
		i++;
	if (env[i] == NULL)
		return (env);
	temp = getcwd(NULL, 0);
	if (!temp)
	{
		perror("minishell");
		free_matrix(env);
		return (NULL);
	}
	temp2 = ft_strjoin("PWD=", temp);
	if (!temp2)
	{
		free(temp);
		perror("minishell");
		free_matrix(env);
		return (NULL);
	}
	free(temp);
	free(env[i]);
	env[i] = temp2;
	return (env);
}
