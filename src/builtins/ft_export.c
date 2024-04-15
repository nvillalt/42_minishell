#include "../../minishell.h"

static void	print_extra_env(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

static char	*add_quotes(char *str)
{
	char *new;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(str) + 3, sizeof(char)); //Blindar
	if (!new)
		exit(1); //Liberar todo y al loro con el status
	while(str[i] != '=')
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = str[i];
	i++;
	j++;
	new[j] = '"';
	j++;
	while(str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '"';
	free(str);
	return (new);
}

static char	*create_new_string(char *str)
{
	char	*temp;

	str = add_quotes(str);
	temp = ft_strjoin("declare -x ", str);
	free(str);
	return(temp);
}

static char	**add_extra_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		env[i] = create_new_string(env[i]);
		i++;
	}
	return (env);
}

static void	swap_lines(char **str1, char **str2)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup(*str1);
	if (!temp1)
		exit(1); //AL LORO
	temp2 = ft_strdup(*str2);
	if (!temp2)
		exit(1); //AL LORO
	free(*str1);
	free(*str2);
	*str1 = temp2;
	*str2 = temp1;
}

static int	print_export_env(char **env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while(env[i + 1] != NULL)
	{
		j = 0;
		while (env[i][j] == env[i + 1][j])
			j++;
		if (env[i][j] > env[i + 1][j])
		{
			swap_lines(&env[i], &env[i + 1]);
			i = -1;
		}
		i++;
	}
	env = add_extra_env(env);
	print_extra_env(env);
	return (0);
}

int	ft_export(char **env, char **cmd)
{
	int		num;
	char	**export_env;

	if (!env)
	{
		ft_putendl_fd("No enviroment founded", STDERR_FILENO);
		return (0);
	}
	num = count_cmds(cmd);
	if (num == 1)
	{
		export_env = env_dup(env);
		print_export_env(export_env);
		free(export_env);
	}
	return (0);
}