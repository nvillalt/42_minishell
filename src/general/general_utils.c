

#include "../../minishell.h"

char	**env_dup(char **env)
{
	char	**dup;
	size_t	i;

	i = 0;
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

int	prompt_loop(t_utils *utils)
{
	char	*input;
	
	while (1)
	{
		readline("minishell: ");
	}
	return (1); // Va todo bien, no da errores
}