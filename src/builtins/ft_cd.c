#include    "../../minishell.h"

static char	*search_for_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while(env[i] && ft_strncmp(env[i], "HOME=", 5) != 0)
		i++;
	if (!env[i])
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		free_matrix(env);
		return(NULL);
	}
	if (!env[i][5])
		return (NULL);
	home = env[i] + 5;
	return (home);
}

static char	**change_to_directory(char **env, char *cmd)
{
	char	*cwd;
	/*
	if (ft_strlen(cmd) > PATH_MAX) // AL LORO
	{
		perror(NULL);
		free(env);
		return (NULL);
	}
	*/
	env = change_old_pwd(env);
	if (!env)
		return (NULL);
	if (chdir(cmd) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(cmd);
		free_matrix(env);
		return (NULL);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", STDERR_FILENO);
		env = change_pwd_error(env, cmd);
		if (!env)
		{
			free(cwd);
			return (NULL);
		}
	}
	else
	{
		env = change_pwd(env);
		if (!env)
		{
			free(cwd);
			return (NULL);
		}
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
	{
		free_matrix(env);
		return (NULL);
	}
	env = change_old_pwd(env);
	if (!env)
		return (NULL);
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(home);
		free_matrix(env);
		return (NULL);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", STDERR_FILENO);
	env = change_pwd(env);
	free(cwd);
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
		perror("minishell");
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
