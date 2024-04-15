#include "../../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	utils.env = env_dup(envp); // Aquí se aloja memoria. Liberarla más adelante.
	utils.path = get_path(utils.env);
	prompt_loop(&utils);
	// Función para liberar al final ????
	free_matrix(utils.env);
	free_matrix(utils.path);
	return (0);
}

// CHECK PARA IMPRIMIR LOS ENV
// int	i = 0;
// while (utils.env[i])
// {
// 	printf("%s\n", utils.env[i]);
// 	i++;
// }
