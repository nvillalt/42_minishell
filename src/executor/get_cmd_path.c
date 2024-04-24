#include "../../minishell.h"

static char	*get_command(t_utils *utils)
{
	char	*command;

	command = ft_strjoin("/", utils->process->cmd[0]);
	if (!command)
	{
		perror(NULL);
		close_fds(utils->process, utils);
		free_utils(utils);
		exit(1); //LIBERAR ABSOLUTAMENTE TODO
	}
	return (command);
}

static char	*get_def_path(char **path, char *command, t_utils *utils)
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
		{
			perror(NULL);
			close_fds(utils->process, utils);
			free_utils(utils);
			exit (1);
		}
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