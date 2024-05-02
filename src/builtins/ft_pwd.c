#include "../../minishell.h"

int ft_pwd(void)
{
	char *str;
	char cwd[PATH_MAX + 1];

	str = getcwd(cwd, PATH_MAX);
	printf("%s\n", str);
	return (0);
}
