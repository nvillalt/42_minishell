

#include "../../minishell.h"

static char	**test_builtins(char *input, char **env) //BORRAR EVENTUALMENTE
{
	char **cmd;
	int	i;

	i = 0;
	cmd = ft_split(input, ' ');
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && ft_strlen(cmd[0]) == 4)
		ft_echo(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && ft_strlen(cmd[0]) == 3)
		ft_pwd();
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && ft_strlen(cmd[0]) == 3)
		ft_env(env, cmd);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0 && ft_strlen(cmd[0]) == 5)
		env = ft_unset(env, cmd);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
		env = ft_cd(env, cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0 && ft_strlen(cmd[0]) == 4)
		ft_exit(cmd); //Ojo que como vamos a hacer exit habrá que liberar todo lo que tengamos hasta el momento
	else if (ft_strncmp(cmd[0], "export", 6) == 0 && ft_strlen(cmd[0]) == 6)
		env = ft_export(env, cmd);
	free_matrix(cmd);
	return (env);
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

int	count_matrix(char **cmds)
{
	int	i;

	i = 0;
	while(cmds[i])
		i++;
	return (i);
}