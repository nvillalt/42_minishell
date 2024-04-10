#include "../../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	if (argc > 1) // meter mensaje de error aquí ????? - Control de que no intenten meter un argumento
		return (1);
	utils.env = env_dup(envp); // Aquí se aloja memoria. Liberarla más adelante.
	utils.path = get_path(utils.env);
	//prompt_loop(&utils);
	ft_pwd(utils.env);
	// Función para liberar al final ????
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
