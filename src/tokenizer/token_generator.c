


#include "../../minishell.h"

//TODO: ver cómo llamar esta funcion mejor

// Quitar comillas, pasar tokens a lista, palabra por palabra
// Quitar redirecciones de la lista (liberar esos nodos)
// Quedarme con esos nodos y pasar a comandos 
// Ojo con el string vacío ""

int	remove_quotes(char *input)
{
	int	i;

	i = 0;
	if (input[i] == 39 || input[i] == 34)
		i++;
	return (i);
}

int	to_token(t_token **tokens, char *input, int i, int j)
{
	t_token	*token;
	char	*str;

	str = ft_substr(input, i, i + j);
	printf("------ >%s\n", str);
//	token = new_token();
	return (1);
}

int	to_token_node(t_utils *utils, char *input)
{
	int	i;
	int	j;

	i = 0;
	if (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
	{
		j = ft_trimspaces(input);
		if (input[j] == 39 || input[j] == 34)
			to_token(utils->token, input, i, j);
		else
			i += j;
	}// Si se va de longitud por norma, cambiar a una funcion aparte
	if (input[i] == 39 || input[i] == 34)
		i++;
	return (i);
}
/* 
	<< heredoc
	>> append
	> outfile
	< infile
	>| (Token >) OK, funciona como > 
	|> funciona como si le pasaras un proceso vacío (son dos tokens, | y >)
	|>> funciona como dos tokens, | - vacío - >>
	>>| ERROR
	<| ERROR
	<<| ERROR
	|<< ERROR
	|< ERROR
	>>> ERROR
	<<< Comportamiento indefinido, here-string, creo que no hay que gestionarlo -> Error ??
	*/

int	add_redirection_to_token(t_token **tokens, char *input)
{
	int	i;
	int	j;

	i = 0;
	if (check_redirections)
	{
		j = 0;
		while (input[j] != 39 || input[j] != 34 ||
			!(input[j] == ' ' || input[j] >= 9 && input[j] <= 13))
			j++;
		
	}
	return (1);
}

int	word_to_token(t_utils *utils, char *input)
{
	int	i;
	int	j;

	i = 0;
	// while (input[i])
	// {
		j = 0;
		input += ft_trimspaces(input);
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			add_redirection_to_token(utils->token, input);
		input += remove_quotes(input); // Quita la primera comilla
		j = to_token_node(utils, input); // Pasa al nodo y dentro quita la comilla del final / medio >>>>>> Avanzar el puntero hasta lo que ya haya quitado
		printf("%s\n", input);
	// 	i += j;
	// }
	return (1);
}