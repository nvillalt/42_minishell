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

void	ft_env(char **env, char **argv)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	if (!control_argv(argv))
	{
		ft_putendl_fd("Error: This command does not accept arguments", STDERR_FILENO);
		return ;
	}
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
