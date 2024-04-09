#include "../minishell.h"

// MAIN
// DUPLICAR EL ENV

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	while (1)
	{
		str = readline("minishell");
		add_history(str);
	}
	return (0);
}
