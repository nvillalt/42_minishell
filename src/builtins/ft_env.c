#include "../../minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = 0;
	if (env == NULL || *env == NULL)
		return ;
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
