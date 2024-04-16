#include "../../minishell.h"

int	prompt_loop(t_utils *utils)
{
	char	*input;
	char	*aux;
	
	while (1)
	{
		input = readline("minishell:");
		if (!*input|| !*aux) // Saltar la linea en blanco
			free(input);
		else
		{
			if (aux)
				free(aux);
			add_history(input);
			if (!check_quotes(input) || !initial_pipe(input))
				printf("ERROR\n"); // Liberación aquí o exit por error
			aux = trim_spaces(input); // hace substr de esto para empezar a limpiar la string
			free(input);
			clean_tokens(utils, aux);
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
	return (0);
}

// CHECK PARA IMPRIMIR LOS ENV
// int	i = 0;
// while (utils.env[i])
// {
// 	printf("%s\n", utils.env[i]);
// 	i++;
// }
