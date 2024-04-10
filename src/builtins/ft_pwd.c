#include "../../minishell.h"

void ft_pwd(char **env)
{
	char *str;
	char cwd[PATH_MAX + 1];

	str = getcwd(cwd, PATH_MAX);
	printf("%s\n", str);
}
