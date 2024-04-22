#include "../../minishell.h"

static char	*get_command(t_utils *utils)
{
	char	*command;

	command = ft_strjoin("/", utils->process->cmd[0]);
	if (!command)
		exit(1); //LIBERAR ABSOLUTAMENTE TODO
	return (command);
}

static char	*get_path_env(char **env, char *command, int *pipex)
{
	int		i;
	char	*mod_env;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], "PATH=", 5)))
		i++;
	if (!env[i])
	{
		perror(NULL);
		free(command);
		//LIBERAR EL RESTO
		exit(1);
	}
	mod_env = env[i] + 5;
	return (mod_env);
}

static char	*get_def_path(char **path, char *command, t_utils *pipex)
{
	int		i;
	int		found;
	char	*search;

	i = 0;
	found = 0;
	while (path[i] && !found)
	{
		search = ft_strjoin(path[i], command);
		if (!search)
			exit(1); //Liberar absolutamente todo
		if (access(search, X_OK) == 0)
			found = 1;
		else
		{
			i++;
			free(search);
		}
	}
	if (!found)
		exit(1); //Liberar absolutamente todo
	return (search);
}

char	*get_cmd_path(t_utils *utils)
{
	char	*search;
	char	*command;

	if (access(utils->process->cmd[0], X_OK) == 0)
		return (utils->process->cmd[0]); //RUTA ABSOLUTA
	command = get_command(utils); //Esto toca liberarlo
	search = get_def_path(utils->path, command, utils);
	free(command);
	return (search);
}