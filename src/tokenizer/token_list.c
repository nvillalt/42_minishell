



#include "../../minishell.h"

t_token *new_token(char *input, int i, int j)
{
	t_token	*new;
	char	*str;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	str = ft_substr(input, i, i + j);
	new->flag = -1;
	new->str = str;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void add_token(t_token **tokens, t_token *new)
{
    t_token *aux;

    printf("Enters here\n");
    if (*tokens == NULL)
    {
        printf("Doesn't enter here\n");
        *tokens = new;
        return;
    }
    aux = *tokens;
    while (aux->next != NULL)
    {
        printf("Aux is not NULL\n");
        aux = aux->next;
    }
    printf("Aux is NULL\n");
    aux->next = new;
    new->prev = aux;
}


// void	add_token(t_token **tokens, t_token *new)
// {
// 	t_token	*aux;

// 	printf("Enters here\n");
// 	if (tokens == NULL)
// 	{
// 		printf("Doesn't enter here");
// 		*tokens = new;
// 		return ;
// 	}
// 	aux = *tokens;
// 	while (aux->next != NULL)
// 		aux = aux->next;
// 	aux->next = new;
// 	new->prev = aux;
// }