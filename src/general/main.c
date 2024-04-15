#include "../../minishell.h"

int	prompt_loop(t_utils *utils)
{
	char	*input;
	int		i;
	int		len;
	
	while (1)
	{
		i = 0;
		len = ft_strlen(input);
		input = readline("minishell: ");
		if (!*input || whitespace_cmp(input)) // El primero es espacio; el segundo, tab.
			free(input);
		else
		{
			add_history(input);
			if (!check_quotes(input) /* && initial_pipe(input)*/)
				printf("ERROR\n");
			i += whitespace_cmp(input); // hace substr de esto para empezar a limpiar la string

		}
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	if (argc > 1) // meter mensaje de error aquí ????? - Control de que no intenten meter un argumento
	{
		printf("This program does not accept arguments.");
		return (1);
	}
	utils.env = env_dup(envp); // Aquí se aloja memoria. Liberarla más adelante.
	utils.path = get_path(utils.env);
	//init_utils(&utils);
	prompt_loop(&utils);
	free_utils(&utils);
	//system("leaks -q minishell");
	return (0);
}

// CHECK PARA IMPRIMIR LOS ENV
// int	i = 0;
// while (utils.env[i])
// {
// 	printf("%s\n", utils.env[i]);
// 	i++;
// }
