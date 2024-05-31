#include "../../minishell.h"

char	**free_str_matrix(char *str, char **matrix)
{
	if (str)
		free(str);
	if (matrix)
		free_matrix(matrix);
	perror("minishell");
	return (NULL);
}
