

#include "../../minishell.h"

static int	strcmp_spaces(char *str)
{
	int	i;

	i = 0;
	while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (1);
}

static char	**test_builtins(char *input, char **env) //BORRAR EVENTUALMENTE
{
	char **argv;
	int	i;

	i = 0;
	argv = ft_split(input, ' ');
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(env, argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		env = ft_unset(env, argv);
	free_matrix(argv);
	return (env);
}

int	prompt_loop(t_utils *utils)
{
	char	*input;
	
	while (1)
	{	
		input = readline("minishell: ");
		if (!input)
			error_message(utils); // ¿¿Quizás codificar esto por tipos de error??? -> un int por tipo
		if (!input || !strcmp_spaces(input)) // El primero es espacio; el segundo, tab.
		{
			// ¿Hay que imprimir algo aquí?
			free(input);
		}
		else
		{
			add_history(input); // preguntar cómo funciona
			utils->env = test_builtins(input, utils->env);
			free(input);
		}
	}
	return (1);
}

char	**env_dup(char **env)
{
	char	**dup;
	size_t	i;

	i = 0;
	if (!env | !*env) //TODO: ver si mejor hacer exit aquí, si no hay env, salir del programa
		return (NULL);
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

void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}