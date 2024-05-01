#include "../../minishell.h"

void	free_mid_matrix(char **dup, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(dup[i]);
		i++;
	}
	free(dup);
}

static char **allocate_memory(char **dup, char **env, int index_jump, int env_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < env_len - 1)
	{
		if (i == index_jump)
			i++;
		dup[j] = ft_strdup(env[i]);
		if (!dup[j])
		{
			perror(NULL);
			free_mid_matrix(dup, j);
			return (NULL);
		}
		i++;
		j++;
	}
	if (i == j)
		return(dup);
	else
	{
		dup[j] = ft_strdup(env[i]);
		if (!dup[j])
		{
			perror(NULL);
			free_mid_matrix(dup, j);
			return (NULL);
		}
	}
	return (dup);
}

char	**unset_var_env(char **env, int index_jump)
{
	char	**dup;
	size_t	env_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
		i++;
	dup = ft_calloc(sizeof(char *), i); //NO SUMAMOS 1 PORQUE EN REALIDAD VAMOS A SALTARNOS UNA LÍNEA
	if (!dup)
	{
		free_matrix(env);
		perror(NULL);
		return (NULL);
	}
	i = 0;
	j = 0;
	env_len = count_matrix(env);
	dup = allocate_memory(dup, env, index_jump, env_len);
	if (!dup)
	{
		perror(NULL);
		return (NULL);
	}
	return (dup);
}