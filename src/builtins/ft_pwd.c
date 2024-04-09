#include "../../minishell.h"

void ft_pwd(char **env)
{
	char *str;

	str = getenv("PWD");
	printf("%s\n", str);
}
