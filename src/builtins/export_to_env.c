#include "../../minishell.h"

static char	**create_new_env(char **env, char *cmd)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc(count_matrix(env) + 2, sizeof(char *));
	if (!new_env)
	{
		free_matrix(env);
		perror("minishell");
		return (NULL);
	}
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_matrix(env);
			free_matrix(new_env);
			perror("minishell");
			return(NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(cmd);
	if (!new_env[i])
	{
		free_matrix(env);
		free_matrix(new_env);
		perror("minishell");
		return (NULL);
	}
	free_matrix(env);
	return (new_env);
}

int	cmd_on_env(char **env, char *cmd)
{
	int	i;
	int	j;
	int	cmd_len;

	i = 0;
	cmd_len = ft_strlen(cmd);
	while(env[i])
	{
		j = 0;
		while(env[i][j] && env[i][j] != '=')
			j++;
		if (ft_strncmp(env[i], cmd, j) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**add_to_env(char **env, char *cmd)
{
	if(!is_string_alpha(cmd))
	{
		ft_putendl_fd("error: Not alpha characters detected", 2);
		return (env);
	}
	env = create_new_env(env, cmd);
	return (env);
}

char	**change_var(char **env, char *cmd)
{
	int		i;
	char	*temp;
	int		var_len;

	var_len = 0;
	while(cmd[var_len] && cmd[var_len] != '=')
		var_len++;
	if (!cmd[var_len])
		return (env);
	i = 0;
	while(ft_strncmp(env[i], cmd, var_len) != 0)
		i++;
	temp = ft_strdup(cmd);
	if (!temp)
	{
		free_matrix(env);
		perror ("minishell");
		return (NULL);
	}
	free(env[i]);
	env[i] = temp;
	return(env);
}

char    **export_to_env(char **env, char **cmd)
{
	int i;

	i = 1;
	while(cmd[i])
	{
		if (cmd_on_env(env, cmd[i]))
		{
			env = change_var(env, cmd[i]);
			if (!env)
				return (NULL);
		}
		else
		{
			env = add_to_env(env, cmd[i]);
			if (!env)
				return (NULL);
		}
		i++;
	}
	return (env);
}