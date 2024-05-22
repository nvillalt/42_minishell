#include "../../minishell.h"

char	**join_var(char **env, char *cmd)
{
	int		i;
	char	*temp;
	int		var_len;
	char	*cmd_value;

	var_len = 0;
	while(cmd[var_len] && cmd[var_len] != '+')
		var_len++;
	if (!cmd[var_len])
		return (env);
	i = 0;
	while(ft_strncmp(env[i], cmd, var_len) != 0 || var_len != env_varlen(env[i]))
		i++;
	var_len = var_len + 2;
	if (!cmd[var_len])
		return (env);
	temp = ft_strjoin(env[i], cmd + var_len);
	if (!temp)
	{
		free_matrix(env);
		perror("minishell");
		return (NULL);
	}
	free(env[i]);
	env[i] = temp;
	return (env);
}

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
	int	plus_flag;

	i = 0;
	cmd_len = 0;
	plus_flag = 0;
	while(cmd[cmd_len] && cmd[cmd_len] != '=')
		cmd_len++;
	if (cmd[cmd_len] == '=' && cmd[cmd_len - 1] == '+' && cmd_len > 1)
	{
		cmd_len--;
		plus_flag = 1;
	}
	while(env[i])
	{
		j = 0;
		while(env[i][j] && env[i][j] != '=')
			j++;
		if ((ft_strncmp(env[i], cmd, cmd_len) == 0) && j == cmd_len)
		{
			if (plus_flag == 1)
				return (2);
			else if (env[i][j] == '=' || !env[i][j])
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

char	**add_to_env(char **env, char *cmd)
{
	if(!is_export_format(cmd))
	{
		ft_putstr_fd("bash: export: \'", STDERR_FILENO); //Cambiar
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
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
	while(ft_strncmp(env[i], cmd, var_len) != 0 || var_len != env_varlen(env[i]))
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
	int	setvar;

	i = 1;
	while(cmd[i])
	{
		setvar = cmd_on_env(env, cmd[i]);
		if (setvar == 1)
		{
			env = change_var(env, cmd[i]);
			if (!env)
				return (NULL);
		}
		else if (setvar == 2)
		{
			env = join_var(env, cmd[i]);
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