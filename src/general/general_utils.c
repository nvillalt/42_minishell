#include "../../minishell.h"

char	**env_dup(char **env)
{
	char	**dup;
	size_t	i;

	i = 0;
//	if (!env | !*env) //TODO: ver si mejor hacer exit aquí, si no hay env, salir del programa
	//	return (NULL);
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
			return (dup); //RETURN DUP??
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

int	ft_strncmp_varlen(char *cmd, char *env_line)
{
	int	cmd_len;
	int	var_len;

	cmd_len = ft_strlen(cmd);
	var_len = 0;
	while(env_line[var_len] && env_line[var_len] != '=')
		var_len++;
	if (ft_strncmp(cmd, env_line, cmd_len) == 0 && cmd_len == var_len)
		return(0);
	else	
		return (1);
}
