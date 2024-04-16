#include    "../../minishell.h"

static char	**change_old_pwd(char **env)
{
	char *temp;
	char cwd[PATH_MAX + 1];
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "OLDPWD", 6) != 0)
		i++;
	if (env[i] == NULL)
		return (env);
	free(env[i]);
	temp = ft_strdup(getcwd(cwd, PATH_MAX));
	if (!temp)
		exit(1); //Liberaciones y demás
	env[i] = ft_strjoin("OLDPWD=", temp);
	if (!env[i])
		exit(1); //Liberaciones y demás
	free(temp);
	return (env);
}

static char	*search_for_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while(env[i] && ft_strncmp(env[i], "HOME", 4) != 0)
		i++;
	if (!env[i])
		return(NULL);
	home = env[i] + 5;
	return (home);
}

static char	**change_to_home(char **env)
{
	char *home;

	home = NULL;
	home = search_for_home(env);
	if (!home)
		return (env);
	env = change_old_pwd(env);
	if (chdir(home) == -1)
	{
		perror(NULL);
		return (env);
	}
	env = change_pwd(env);
	return (env);
}

static int	check_pwds(char **env)
{
	int	i;

	i = 0;
	while(env[i] && ft_strncmp(env[i], "HOME", 4) != 0)
		i++;
	if (!env[i])
		return (0);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "OLDPWD", 6) != 0)
		i++;
	if(!env[i])
		return (0);
	return (1);
}

char **ft_cd(char **env, char **cmd)
{
	int	i;
	
	if (env == NULL)
	{
		ft_putendl_fd("Can not reach variable PWD in the enviroment", STDERR_FILENO);
		return (NULL);
	}
	if (!check_pwds(env))
		return(env);
	i = 0;
	while(cmd[i])
		i++;
	if (i == 1)
		env = change_to_home(env);
	else if (i == 2)
		env = change_to_directory(env, cmd[1]);
	else
	{
		ft_putendl_fd("Error: This command does not accept more than 2 arguments", STDERR_FILENO);
		return (NULL);
	}
	return (env);
}