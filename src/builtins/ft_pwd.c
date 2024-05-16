#include "../../minishell.h"

int ft_pwd(void)
{
	char *str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		perror("minishell");
		return (1);
	}
	printf("%s\n", str);
	free(str);
	return (0);
}
