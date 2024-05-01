


#include "../../minishell.h"

int	clear_token_list(t_token **token_list)
{
	t_token	*aux;
	t_token	*next;

	aux = *token_list;
	while (aux->next != NULL)
	{
		next = aux->next;
		if (aux->str)
			free(aux->str);
		free(aux);
		aux = next;
	}
	free(aux);
	*token_list = NULL;
	return (1);
}

int	new_token(t_token **new)
{
	*new = ft_calloc(sizeof(t_token), 1);
	if (!(*new))
		return (0);
	(*new)->str = NULL;
	(*new)->next = NULL;
	return (1);
}

int	add_token(t_token **token_list, t_token *new)
{
	t_token	*tmp;

	if (!token_list || !new)
		return (0);
	if (*token_list == NULL)
	{
		*token_list = new;
		return (1);
	}
	tmp = *token_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}