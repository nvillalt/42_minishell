

#include "../../minishell.h"

void	init_utils(t_utils *utils)
{
	if (!utils->env || !utils->path)
		error_message(utils);
	utils->heredoc = 0;
	utils->parse = NULL;
	utils->token = NULL;
	// utils->parse->builtin = NULL;
	// utils->parse->cmd = NULL;
	// utils->parse->redir->doc = NULL;
	// utils->parse->redir->flag = -1;
}

char	**env_dup(char **env)
{
	char	**dup;
	size_t	i;

	i = 0;
	if (!env) //TODO: ver si mejor hacer exit aquí, si no hay env, salir del programa
		return (NULL);
	while (env[i] != NULL)
		i++;
	dup = ft_calloc(sizeof(char *), i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while(env[i] != NULL)
	{
		dup[i] = ft_strdup(env[i]);
		if (!dup[i])
		{
			free_matrix(dup);
			return (dup);
		}
		i++;
	}
	return (dup);
}
