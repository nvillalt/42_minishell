#include "../../minishell.h"

int ft_pwd(int argc, char **argv, char **env)
{
	char *str;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(env[i] && ft_strncmp(env[i], "PWD", 3) != 0)
		i++;
	if (!env[i])
		perror("error");
	while(env[i][j])
		j++;
	str = getcwd(str, j - 4);
	printf("%d\n", j - 4);
	printf("%s\n", str);
	free(str);
	system("leaks -q a.out");
	return 0;
}
