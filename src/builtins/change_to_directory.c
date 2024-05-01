#include "../../minishell.h"

static char	**change_old_pwd_dir(char **env, char *old_pwd)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "OLDPWD", 6) != 0)
		i++;
	if (env[i] == NULL)
		return (env);
	temp = ft_strjoin("OLDPWD=", old_pwd);
	if (!temp)
	{
		perror(NULL);
		free_matrix(env);
		return (NULL);
	}
	free(env[i]);
	env[i] = temp;
	return (env);
}

char	**change_to_directory(char **env, char *cmd)
{
	char *old_pwd;
	char cwd[PATH_MAX + 1]; //Ojo con el +1

	if (ft_strlen(cmd) > PATH_MAX)
	{
		ft_putendl_fd("error: Path name too long", 2); //Al loro con esto
		return (env);
	}
	old_pwd = ft_strdup(getcwd(cwd, PATH_MAX));
	if (!old_pwd)
	{
		perror(NULL);
		free_matrix(env);
		return (NULL);
	}
	if (chdir(cmd) == -1)
	{
		perror(NULL);
		free(old_pwd);
		return (env);
	}
	env = change_old_pwd_dir(env, old_pwd);
	if (!env)
	{
		free(old_pwd);
		return (NULL);
	}
	env = change_pwd(env);
	if (!env)
	{
		free(old_pwd);
		return (NULL);
	}
	return (env);
}
