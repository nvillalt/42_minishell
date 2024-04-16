#include "../../minishell.h"

static char	**change_old_pwd_dir(char **env, char *old_pwd)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "OLDPWD", 6) != 0)
		i++;
	if (env[i] == NULL)
		return (env);
	free(env[i]);
	env[i] = ft_strjoin("OLDPWD=", old_pwd);
	if (!env[i])
	{
		free(old_pwd);
		exit(1); //Liberaciones y demás
	}
	return (env);
}

char	**change_pwd(char **env)
{
	char *temp;
	char cwd[PATH_MAX + 1];
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD", 3) != 0)
		i++;
	if (env[i] == NULL)
		return (env);
	free(env[i]);
	temp = ft_strdup(getcwd(cwd, PATH_MAX));
	if (!temp)
		exit(1); //Liberaciones y demás
	env[i] = ft_strjoin("PWD=", temp);
	if (!env[i])
		exit(1); //Liberaciones y demás
	free(temp);
	return (env);
}

char	**change_to_directory(char **env, char *cmd)
{
	char *old_pwd;
	char cwd[PATH_MAX + 1]; //Ojo con el +1

	old_pwd = ft_strdup(getcwd(cwd, PATH_MAX));
	if (chdir(cmd) == -1)
	{
		perror(NULL);
		free(old_pwd);
		return (env);
	}
	env = change_old_pwd_dir(env, old_pwd);
	env = change_pwd(env);
	return (env);
}