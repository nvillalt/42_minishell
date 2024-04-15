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

void	clear_tokens(t_token **tokens)
{
	t_token	*aux;

	while (*tokens)
	{
		aux = (*tokens)->next;
		if ((*tokens)->str)
			free((*tokens)->str);
		free(*tokens);
		*tokens = aux;
	}
	*tokens = NULL;
}

void	free_utils(t_utils *utils)
{
	if (utils->env)
		free_matrix(utils->env);
	if (utils->path)
		free_matrix(utils->path);
	if (utils->token)
		clear_tokens(utils->token);
}