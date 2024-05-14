#include    "../../minishell.h"

static char	*search_for_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while(env[i] && ft_strncmp(env[i], "HOME", 4) != 0)
		i++;
	if (!env[i])
	{
		ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
		free_matrix(env);
		return(NULL);
	}
	home = env[i] + 5;
	return (home);
}

static char	**change_to_directory(char **env, char *cmd)
{
	if (ft_strlen(cmd) > PATH_MAX) // AL LORO
	{
		perror(NULL);
		printf("entra\n");
		free(env);
		return (NULL);
	}
	env = change_old_pwd(env);
	if (!env)
		return (NULL);
	if (chdir(cmd) == -1)
	{
		perror(NULL);
		free_matrix(env);
		return (NULL);
	}
	env = change_pwd(env);
	if (!env)
		return (NULL);
	return (env);
}

static char	**change_to_home(char **env)
{
	char *home;

	home = search_for_home(env);
	if (!home)
		return (NULL);
	env = change_old_pwd(env);
	if (!env)
		return (NULL);
	if (chdir(home) == -1)
	{
		free_matrix(env);
		perror(NULL);
		return (NULL);
	}
	env = change_pwd(env);;
	if (!env)
		return (NULL);
	return (env);
}

int	ft_cd(t_utils *utils, char **cmd)
{
	int		i;
	char	**env;

	i = 0;
	env = env_dup(utils->env);
	if (!env)
	{
		perror(NULL);
		return (1);
	}
	while(cmd[i])
		i++;
	if (i == 1)
	{
		env = change_to_home(env);
		if (!env)
			return (1);
	}
	else if (i == 2)
	{
		env = change_to_directory(env, cmd[1]);
		if (!env)
			return (1);
	}
	else
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		free_matrix(env);
		return (1);
	}
	free_matrix(utils->env);
	utils->env = env;
	return (0);
}
