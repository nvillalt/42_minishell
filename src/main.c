#include "../minishell.h"

// MAIN
// DUPLICAR EL ENV

int	main(int argc, char **argv, char **envp)
{
	// DUPLICAR ENVP, strdup en doble matriz. Ver que no de segfault si me quitan en envp al empezar (que dé error y ya)
	printf("Hola");
	return (0);
}
