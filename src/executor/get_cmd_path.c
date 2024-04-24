#include "../../minishell.h"

static char	*get_command(t_utils *utils)
{
	char	*command;

	command = ft_strjoin("/", utils->process->cmd[0]);
	if (!command)
	{
		free(command);
		exit_process(utils);
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
			free(command);
			exit_process(utils);
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
	{
		free(command);
		return (NULL);
	}
	free(command);
	return (search);
}

char	*get_cmd_path(t_utils *utils)
{
	char	*search;
	char	*command;

	if (access(utils->process->cmd[0], X_OK) == 0)
		return (utils->process->cmd[0]);
	command = get_command(utils);
	search = get_def_path(utils->path, command, utils);
	return (search);
}