

#include "../../minishell.h"

static int	strcmp_spaces(char *str)
{

}

int	prompt_loop(t_utils *utils)
{
	char	*input;
	
	while (1)
	{	
		input = readline("minishell: ");
		if (!input)
			error_message(utils); // ¿¿Quizás codificar esto por tipos de error???
		if (!input || ) // El primero es espacio; el segundo, tab.
		{
			printf("%d", ft_strcmp(input, " \n"));
			printf("debug\n");
			free(input);
		}
		else
		{
			add_history(input);
			free(input);
		}
	}
	return (1); // Va todo bien, no da errores
}

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