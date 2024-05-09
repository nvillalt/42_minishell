/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:07:53 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/09 19:07:59 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*find_env_path(char **env)
{
	char	*str;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			str = ft_strtrim(env[i], "PATH=");
		i++;
	}
	return (str);
}

char	**get_path(char **env)
{
	char	**path;
	char	*aux;
	char	*oneline;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	oneline = find_env_path(env);
	path = ft_split(oneline, ':');
	while (path[i])
	{
		aux = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = aux;
		i++;
	}
	free(oneline);
	return (path);
}
