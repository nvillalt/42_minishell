#include "../../minishell.h"

void	exit_matrix_str(char *str, char **matrix, char *error_str, t_utils *utils)
{
	if (str)
		free(str);
	if (matrix)
		free(matrix);
	perror(error_str);
	exit_process(utils);
}