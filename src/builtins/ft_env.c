#include "../../minishell.h"

static int	control_argv(char **argv)
{
	int	i;

	i = 0;
	while(argv[i])
		i++;
	if (i == 1)
		return (1);
	else
		return (0);
}

static int	equal_in_str(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_env(char **env, char **argv)
{
	int	i;

	i = 0;
	if (!env)
		return (1) ; // CONSTRUIR PATH??
	if (!control_argv(argv))
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd("\'", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd("\' ", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (1);
	}
	while(env[i])
	{
		if (equal_in_str(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
