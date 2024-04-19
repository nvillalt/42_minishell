


#include "../../minishell.h"

//TODO: ver cómo llamar esta funcion mejor

// Quitar comillas, pasar tokens a lista, palabra por palabra
// Quitar redirecciones de la lista (liberar esos nodos)
// Quedarme con esos nodos y pasar a comandos 
// Ojo con el string vacío ""


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

