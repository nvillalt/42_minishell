#include "../../minishell.h"

static char	**replace_oldpwd(char **env, int i)
{
	char	*temp;

	temp = ft_strdup("OLDPWD");
	if (!temp)
		return (NULL);
	free(env[i]);
	env[i] = temp;
	return (env);
}

static char	**create_oldpwd(char **env, int i)
{
	char	**new_env;

	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	new_env[i] = ft_strdup("OLDPWD");
	if (!new_env[i])
		return (NULL);
	free_matrix(env);
	return(new_env);
}

char	**set_oldpwd(char **env)
{
	int		i;

	i = 0;
	while(env[i] && ft_strncmp_varlen("OLDPWD", env[i]))
		i++;
	if (env[i])
	{
		env = replace_oldpwd(env, i);
		if (!env)
			return (NULL);
	}
	else
	{
		env = create_oldpwd(env, i);
		if (!env)
			return (NULL);
	}
	return (env);
}