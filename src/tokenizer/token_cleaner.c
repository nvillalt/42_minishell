

// #include "../../minishell.h"

// char	*trim_spaces(char *input)
// {
// 	char	*str;
// 	int		i;
// 	int		len;

// 	i = whitespace_cmp(input);
// 	len = ft_strlen(input);
// 	if (*input == '\0')
// 		return (NULL);
// 	while (is_whitespace(input[len - 1]))
// 		len--;
// 	str = ft_substr(input, i, len - i);
// 	return(str);
// }
// char	*remove_quotes(char *process)
// {
// 	int		i;
// 	int		flag;
// 	char	*aux;

// 	i = 0;
// 	aux = trim_spaces(process);
// 	printf("%s\n", aux);

// }
// // "    " | pinga | "" | holaaa CHECAR CON ESTO

// /*- Buscar pipe -> Guardarme el nodo de los procesos 
// (Cuidado con la excepcion de "|")
// - Dentro de cada proceso ir leyendo letra a letra
// --> Si encuentro " tratarlo como una string lo que sea que lleve las comillas, 
// da igual cómo estén. Aunque estén entre medias
// --> Si no encuentro comillas, 
// saltar espacios/is_whitespace
// --> Ver redirecciones válidas/caracteres especiales 
// y la palabra que venga ddetrás que va a ser la que tenga la flag*/

// int	clean_tokens(t_utils *utils, char *aux)
// {
// 	t_token	*token_list;
// 	t_token	*token;
// 	char	*temp;

// 	token_list = NULL;
// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		return (0);
// 	printf("Puntero en clean tokens: %p\n", &aux);
// 	temp = new_token(&token, &aux);

// 	parse_tokens(utils, &token_list);
// 	return (1);
// }

// // void	clean_tokens(t_utils *utils, char *aux)
// // {
// // 	char	*temp;
// // 	t_token	*token_list;
// // 	t_token	*token;
// // 	t_token	*tmp; // Solo para imprimir

// // 	token = NULL;
// // 	token_list = NULL;
// // 	while (*aux != '\0')
// // 	{
// // 		token = new_token(&aux); // Viene con memoria alojada
// // 		// if (is_whitespace(token->str[0]))
// // 		// {
// // 		// 	temp = trim_spaces(token->str);
// // 		// 	free(token->str);
// // 		// 	token->str = temp;
// // 		// }
// // 		add_token(&token_list, token);
// // 	}
// // 	printf("PRINTING LIST\n");
// // 	tmp = token_list;
// // 	int	i = 1;
// // 	printf("-->Token %d: %s\n", i++, tmp->str);
// // 	while (tmp->next != NULL)
// // 	{
// // 		tmp = tmp->next;
// // 		printf("-->Token %d: %s\n", i++, tmp->str);
// // 	}
// // 	parse_tokens(utils, &token_list);
// // 	//clear_token_list(&token_list); // Liberar aquí toda la lista
// // 	//free_utils(utils);
// // }
