#include "../../minishell.h"

int ft_pwd(char **env)
{
	char *str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		str = ft_getenv(env, "PWD");
		if (!str)
		{
			ft_putendl_fd("minishell: PWD not set", STDERR_FILENO);
			return (1);
		}
		str = ft_strdup(str);
		if (!str)
			return (1);
	}
	printf("%s\n", str);
	free(str);
	return (0);
}
