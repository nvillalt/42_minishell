


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

int	to_token_node(t_utils *utils, char *input)
{
	int	i;

	i = 0;
	if (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
		i++;
	
	i = remove_quotes(input);

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

int	word_to_token(t_utils *utils, char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		input += ft_trimspaces(input);
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			check_redirections(utils, input);
		input += remove_quotes(input); // Quita la primera comilla
		j = to_token_node(utils, input); // Pasa al nodo y dentro quita la comilla del final / medio >>>>>> Avanzar el puntero hasta lo que ya haya quitado
		printf("%s\n", input);
		i += j;
	}
	return (1);
}