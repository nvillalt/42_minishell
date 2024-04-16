#include "../../minishell.h"

static char	**duplicate_env(char **env)
{
	int	i;
	int	len;
	char	**new_env;

	i = 0;
	len = count_matrix(env);
	new_env = ft_calloc(len + 1, sizeof(char *));
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (new_env);
}

static void	print_export_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while(env[i])
	{
		j = 0;
		printf("declare -x ");
		while(env[i][j] && env[i][j] != '=')
		{
			printf("%c", env[i][j]);
			j++;
		}
		if (!env[i][j])
		{
			i++;
			printf("\n");
		}
		else
		{
			printf("%c", env[i][j]);
			j++;
			printf("%c", '\"');
			while(env[i][j])
			{
				printf("%c", env[i][j]);
				j++;
			}
			printf("%c", '\"');
			printf("\n");
			i++;
		}
	}
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

static int	sort_export_env(char **env)
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
	return (0);
}

char	**ft_export(char **env, char **cmd)
{
	int		num;
	char	**export_env;

	num = count_matrix(cmd);
	if (!env)
	{
		ft_putendl_fd("No enviroment founded", STDERR_FILENO);
		return (env);
	}
	if (num == 1)
	{
		export_env = env_dup(env); //Al loro con este duplicado
		sort_export_env(export_env);
		print_export_env(export_env);
		free_matrix(export_env);
	}
	else if (num > 1)
		env = export_to_env(env, cmd);
	return (env);
}