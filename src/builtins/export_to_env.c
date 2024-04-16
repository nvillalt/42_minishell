#include "../../minishell.h"

static char	**create_new_env(char **env, char *cmd)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc(count_matrix(env) + 2, sizeof(char *));
	if (!new_env)
		exit(1); //Al loro con liberar todo
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			exit(1); //Al loro con liberar todo
		i++;
	}
	new_env[i] = ft_strdup(cmd);
	free_matrix(env);
	return (new_env);
}

static int	is_string_alpha(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && ft_isalpha(cmd[i]))
		i++;
	if (cmd[i] == 0)
		return (1);
	else
		return (0);
}

static char	**add_to_env(char **env, char *cmd)
{
	if(!is_string_alpha(cmd))
	{
		ft_putendl_fd("error: Not alpha characters detected", 2);
		return (env);
	}
	env = create_new_env(env, cmd);
	return (env);
}

char    **export_to_env(char **env, char **cmd)
{
	int i;

	i = 1;
	while(cmd[i])
	{
		env = add_to_env(env, cmd[i]);
		i++;
	}
	return (env);
}