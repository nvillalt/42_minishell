#include "../../minishell.h"

static char	*find_env_path(char **env)
{
	char	*str;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i]);
		i++;
	}
	return (NULL);
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
			free_matrix(path);
			free(command);
			perror("minishell");
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
	free(command);
	if (!found) //CUIDADO CON ESTO
		return (NULL);
	return (search);
}

char	*get_cmd_path(t_utils *utils, t_parse *process, int *flag)
{
	char	*search;
	char	*path_oneline;
	char	**path;
	char	*command;

	if (access(process->cmd[0], X_OK) == 0)
		return (process->cmd[0]);
	path_oneline = find_env_path(utils->env);
	if (!path_oneline)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(process->cmd[0]);
		exit_process_custom(utils, 127);
	}
	path_oneline = ft_strdup(path_oneline);
	if (!path_oneline)
	{
		perror("minishell");
		exit_process(utils);
	}
	path = ft_split(path_oneline, ':');
	free(path_oneline);
	if (!path)
	{
		perror("minishell");
		exit_process(utils);
	}
	command = ft_strjoin("/", process->cmd[0]);
	if (!command)
	{
		perror("minishell");
		free_matrix(path);
		exit_process(utils);
	}
	search = get_def_path(path, command, utils);
	free_matrix(path);
	return (search);
}
