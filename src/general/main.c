


#include "../../minishell.h"

int	prompt_loop(t_utils *utils)
{
	char	*input;
	
	while (1)
	{	
		input = readline("minishell: ");
		if (!input)
			error_message(utils); // ¿¿Quizás codificar esto por tipos de error??? -> un int por tipo
		if (!*input || !strcmp_spaces(input)) // El primero es espacio; el segundo, tab.
			free(input);
		else
		{
			add_history(input); // preguntar cómo funciona
			input += ft_trimspaces(input);
			if (!check_quotes(input))
				error_message(utils);
			printf("%s\n", input); // Parseo, eliminar
			word_to_token(utils, input);
			// -> Gestion de comillas + espacios entre comillas
			// Empezar a pasar a lista de tokens - 1) ls, 2) -la 3)"ls -la" 4)| 
			//free(input);
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
	init_utils(&utils);
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