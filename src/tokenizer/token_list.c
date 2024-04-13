



#include "../../minishell.h"

t_token *new_token(char *input)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->flag = -1;
	new->str = NULL;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*aux;

	aux = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new;
	aux->prev = aux;
}