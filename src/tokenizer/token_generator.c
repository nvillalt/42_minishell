


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
// t_parse	*init_process(void)
// {
// 	t_parse	*process;

// 	process = ft_calloc(sizeof(t_parse), 1);
// 	if (!process)
// 		return (NULL); // O exit??
// 	process->cmd = NULL;
// 	process->built_in = 0;
// 	process->redirec = NULL;
// 	process->next = NULL;
// 	return (process);
// }

// t_parse	*clean_process(t_token *tmp)
// {
// 	t_parse	*new_node;
// 	int		flag;
// 	int		i;

// 	i = 0;
// 	flag = 0;
// 	new_node = init_process();
// 	while (tmp->str[i])
// 	{
// 		if (tmp->str[i] && flag == 0)
// 			check_redirections(tmp->str); // Extraer la redirección, checar que está bien y después ver que funciona el siguiente chisme (doc)
// 		else if ((tmp->str[i] == 34 || tmp->str[i] == 39) && tmp->str[i] == flag)
// 			flag = 0;
// 		if (tmp->str[i] == flag && flag )
// 		i++;
// 	}
// 	return (new_node);
// }

// void	parse_tokens(t_utils *utils, t_token **token_list)
// {
// 	t_token	*tmp;
// 	t_parse	*new;

// 	new = NULL;
// 	tmp = *token_list;
// 	utils->process = NULL; // O init_process??
// 	while (tmp->next != NULL)
// 	{
// 		new = clean_process(tmp);
// 		add_process(&utils->process, new);
// 		tmp = tmp->next;
// 	}
// }