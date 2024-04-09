#include "../../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	if (argc > 1) // meter mensaje de error aquí ????? - Control de que no intenten meter un argumento
		return (1);
	utils.env = env_dup(envp); // Aquí se aloja memoria. Liberarla más adelante.
	prompt_loop(&utils);
	// Función para liberar al final ????
	return (0);
}

// CHECK PARA IMPRIMIR LOS ENV
// int	i = 0;
// while (utils.env[i])
// {
// 	printf("%s\n", utils.env[i]);
// 	i++;
// }
