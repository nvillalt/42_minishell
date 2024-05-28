#include "../../minishell.h"

static char **allocate_newenv(char **dup, char **env, int index_jump, int env_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (index_jump == 0)
		i++;
	while(i < env_len)
	{
		dup[j] = ft_strdup(env[i]);
		if (!dup[j])
		{
			perror("minishell");
			free_matrix(env);
			free_matrix(dup);
			return (NULL);
		}
		j++;
		i++;
		if (i == index_jump)
			i++;
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
	dup = ft_calloc(sizeof(char *), i + 1); //NO SUMAMOS 1 PORQUE EN REALIDAD VAMOS A SALTARNOS UNA LÍNEA
	if (!dup)
	{
		free_matrix(env);
		perror("minishell");
		return (NULL);
	}
	dup = allocate_newenv(dup, env, index_jump, i);
	if (!dup)
		return (NULL);
	return (dup);
}
