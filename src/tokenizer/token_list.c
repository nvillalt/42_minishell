



#include "../../minishell.h"



// int	get_process(char *input, char **str)
// {
// 	int		i;
// 	int		flag;

// 	i = 0;
// 	flag = 0;
// 	while (input[i])
// 	{
// 		if ((input[i] == 34 || input[i] == 39) && flag == 0)
// 			flag = input[i]; // Entro en estado de hay comillas, no salgo hasta que encuentre otras comillas
// 		else if ((input[i] == 34 || input[i] == 39) && input[i] == flag)
// 			flag = 0;
// 		if (is_whitespace(input[i]) && flag == 0) // No ha entrado en el estado de comillas así que lo que encuentra, no es un caracter
// 			break ;
// 		i++;
// 	}
// 	*str = ft_substr(input, 0, i);
// 	printf("%s\n", *str);
// //	return (i);
// }
void	clear_token_list(t_token **token_list)
{
	t_token	*aux;
	t_token	*next;

	aux = *token_list;
	while (aux->next != NULL)
	{
		next = aux->next;
		free(aux);
		aux = next;
	}
	free(aux);
	*token_list = NULL;
}

char	*get_process(char **input)
{
	char	*str;
	int		flag;
	int		i;

	i = 0;
	flag = 0;		// NO LIBERAR LA STR DE DONDE VIENE TODO, SOLO AVANZAR Y COGER DOS CONTADORES

	return (str);
}

char	*new_token(t_token **token, char **input)
{
	printf("Puntero en new token: %p\n", input);
	(*token)->str = get_process(input);
}

// t_token *new_token(t_token **token, char *input)
// {
// 	t_token	*new;
// 	char	*str;
// 	char	*aux;
// 	int		num;

// 	num = 0;
// 	str = NULL;
// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	num = get_process(*input, &str);
// 	if (*input[0] != '\0') // Revisar aquí y ver que no hay problemas de memoria por el ft_substr
// 		aux = ft_substr(*input, num, ft_strlen(*input));
// 	free(*input);
// 	*input = aux;
// 	printf("%s\n", *input);
// //	free(aux);
// //	printf("~~~~~~~~>str:%s\n", *input);
// 	new->str = str;
// 	new->next = NULL;
// 	return (new);
// }

void	add_token(t_token **token_list, t_token *new)
{
	t_token	*tmp;

	if (!token_list || !new)
		return ;
	if (*token_list == NULL)
	{
		*token_list = new;
		return ;
	}
	tmp = *token_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}