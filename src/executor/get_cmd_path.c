/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:18 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 17:20:26 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_ispath(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_env_path(t_utils *utils, t_parse *process)
{
	char	*env_ptr;
	char	*path_oneline;

	env_ptr = ft_getenv(utils->env, "PATH");
	if (!env_ptr)
		exit_process_path(utils, process, 127);
	path_oneline = ft_strdup(env_ptr);
	if (!path_oneline)
		exit_matrix_str(NULL, NULL, "minishell", utils);
	return (path_oneline);
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
			exit_matrix_str(command, path, "minishell", utils);
		if (access(search, X_OK) == 0)
			found = 1;
		else
		{
			i++;
			free(search);
		}
	}
	free(command);
	if (!found)
		return (NULL);
	return (search);
}

char	*get_cmd_path(t_utils *utils, t_parse *process)
{
	char	*search;
	char	*path_oneline;
	char	**path;
	char	*command;

	if (access(process->cmd[0], X_OK) == 0)
		return (process->cmd[0]);
	if (access(process->cmd[0], X_OK) == -1 && ft_ispath(process->cmd[0]))
		exit_process_path(utils, process, 127);
	path_oneline = get_env_path(utils, process);
	path = ft_split(path_oneline, ':');
	free(path_oneline);
	if (!path)
		exit_matrix_str(NULL, NULL, "minishell", utils);
	command = ft_strjoin("/", process->cmd[0]);
	if (!command)
		exit_matrix_str(NULL, path, "minishell", utils);
	search = get_def_path(path, command, utils);
	free_matrix(path);
	return (search);
}
