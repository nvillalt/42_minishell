#include "../../minishell.h"

static void	print_extra_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while(env[i])
	{
		printf("declare -x ");
		j = 0;
		while(env[i][j] != '=')
		{
			printf("%c", env[i][j]);
			j++;
		}
		printf("\"");
		while(env[i][j])
		{
			printf("%c", env[i][j]);
			j++;
		}	
		printf("\"");
		printf("\n");
		i++;
	}
}

static void	swap_lines(char **str1, char **str2)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup(*str1);
	if (!temp1)
		exit(1);
	temp2 = ft_strdup(*str2);
	if (!temp2)
		exit(1);
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
	print_extra_env(env);
	return (0);
}

static char	**create_new_env(char **env, char *cmd)
{
	int		i;
	char	**new_env;

	i = 0;
	while(env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		exit(1); //AL LORO CON EL STATUS Y CON BORRAR LO QUE TOCA
	i = 0;
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			exit(1); //LIBERACIONES Y DEMÁS
		i++;
	}
	new_env[i] = cmd; //AQUÍ ESTÁ ROTO
	free_matrix(env);
	return(new_env);
}

static char	**add_to_env(char **cmd, char **env)
{
	int	i;
	int	j;

	i = 1;
	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j] && cmd[i][j] != '=')
			j++;
		if (cmd[i][j])
			env = create_new_env(env, cmd[i]);
		i++;
	}
	return (env);
}

int	ft_export(char **env, char **cmd) //Vamos a pasar por referencia o dentro de la estructura un doble char ** como secreto para cuando haces un export sin =
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
	else if (num > 1)
	{
		env = add_to_env(cmd, env);
	}
	return (0);
}
