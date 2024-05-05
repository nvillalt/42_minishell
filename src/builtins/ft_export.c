#include "../../minishell.h"

static void print_no_value(char **env, int *i, int *j)
{
	printf("%c", env[*i][*j]);
	(*j)++;
	printf("%c", '\"');
	while(env[*i][*j])
	{
		printf("%c", env[*i][*j]);
		(*j)++;
	}
	printf("%c", '\"');
	printf("\n");
	(*i)++;
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
			print_no_value(env, &i, &j);
	}
}

static int	swap_lines(char **str1, char **str2)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup(*str1);
	if (!temp1)
	{
		perror(NULL);
		return (0);
	}
	temp2 = ft_strdup(*str2);
	if (!temp2)
	{
		free(temp1);
		perror(NULL);
		return (0);
	}
	free(*str1);
	free(*str2);
	*str1 = temp2;
	*str2 = temp1;
	return (1);
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
			if(!swap_lines(&env[i], &env[i + 1]))
			{
				free_matrix(env);
				return (FUNC_FAILURE);
			}
			i = -1;
		}
		i++;
	} 
	return (FUNC_SUCCESS);
}

int	ft_export(t_utils *utils, char **cmd)
{
	int		num;
	char	**export_env;

	export_env = env_dup(utils->env); //AL LORO CON ESTE DUPLICADO
	if (!export_env)
		return (1);
	num = count_matrix(cmd);
	if (!num)
	{
		ft_putendl_fd("minishell: env: No such file or directory", STDERR_FILENO);
		return (127);
	}
	if (num == 1)
	{
		if(!sort_export_env(export_env))
			return (1);
		print_export_env(export_env);
		free_matrix(export_env);
	}
	else if (num > 1)
	{
		export_env = export_to_env(export_env, cmd);
		if (!export_env)
			return (1);
		free_matrix(utils->env);
		utils->env = export_env;
	}
	return (0);
}