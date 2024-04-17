#include "../../minishell.h"

static char	**create_mini_env(void)
{
	char	**env;
	char	*new_cwd;
	char	*join;
	char	cwd[PATH_MAX + 1];

	env = ft_calloc(4, sizeof(char *));
	new_cwd = getcwd(new_cwd, PATH_MAX);
	env[0] = ft_strjoin("PWD=", new_cwd);
	if(!env[0])
		exit(1); // Controlar
	env[1] = ft_strdup("SHLVL=1");
	if(!env[1])
		exit(1); //Controlar
	env[2] = ft_strdup("_=/usr/bin/env");
	if(!env[2])
		exit(1); //Controlar
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	if(!*envp)
		utils.env = create_mini_env();
	else
	{
		utils.env = env_dup(envp); // Aquí se aloja memoria. Liberarla más adelante.
		utils.path = get_path(utils.env);
	}
//	utils.env = set_oldpwd(utils.env);
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
