

#include "../../minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return ;
}

void	free_utils(t_utils *utils)
{
	if (utils->env)
		free_matrix(utils->env);
	if (utils->path)
		free_matrix(utils->path);
}