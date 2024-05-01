



#include "../../minishell.h"

char	*trim_spaces(char *input)
{
	char	*str;
	int		i;
	int		len;

	i = whitespace_cmp(input);
	len = ft_strlen(input);
	if (*input == '\0')
		return (NULL);
	while (is_whitespace(input[len - 1]))
		len--;
	str = ft_substr(input, i, len - i);
	return(str);
}

int	get_substr(char *aux, int i)
{
	int	flag;

	flag = 0;
	while (aux[i])
	{
		if ((aux[i] == 34 && aux[i + 1] == 34) || (aux[i + 1] == 39 && aux[i + 1] == 39)
			&& !ft_strncmp(aux + 2, "echo", 4))
			return (2);
		else if (!ft_strncmp(aux, "echo", 4) && (aux[4] == 34 && aux[4 + 1] == 34)
			|| (aux[4 + 1] == 39 && aux[4 + 1] == 39))
			return (4);
		if ((aux[i] == 34 || aux[i] == 39) && flag ==  0)
			flag = aux[i];
		else if (aux[i] == flag)
			flag = 0;
		if (is_whitespace(aux[i]) && flag == 0) // No ha entrado en el estado de comillas así que lo que encuentra, no es un caracter
 			break ;
		i++;
	}
	return (i);
}

int	check_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{	// Retornar aquí el código de error que ponga echo $?. Ver en 42
		if (check_redirections(str) == 2 || check_redirections(str) == 8)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `>'", 2);
			return (2);
		}
		else if (check_redirections(str) == 9 || check_redirections(str) == 4)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
			return (2);
		}
		else if (check_redirections(str) == 6)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
			return (2);
		}
		i++;
	}
	return (1);
}

int	free_tokens(t_token **token_list, char *temp, int n)
{
	clear_token_list(token_list);
	free(temp);
	if (n == 1)
		return (2); // Error de syntax error
	return (0); // Ejecución exitosa
}
// Primero extraigo el token, luego compruebo como está. Si está mal, libero string + nodos que hubiera alojados.
int	get_tokens(char	*aux, t_utils *utils)
{
	t_token	*token_list;
	t_token	*token;
	char	*temp;
	int		i;
	int		j;

	token_list = NULL;
	token = NULL;
	i = 0;
	j = 0;
	while (aux[i])
	{
		j = get_substr(aux, i);
		if (!new_token(&token) && token_list != NULL)
			clear_token_list(&token_list);
		temp = ft_substr(aux, i, (j - i));
		if (check_symbol(temp) == 1) // Solo metes en el nodo la mierda si está bien, si no, no
			token->str = temp;
		if (!add_token(&token_list, token) || token->str == NULL) // Si no se ha guardado cosa en el nodo, liberar todo pq está mal.
			return (free_tokens(&token_list, temp, 1)); // Parece ser que 2 es lo que retorna bash cuando hay unexpected token
		while (is_whitespace(aux[j]))
			j++;
		i = j;
		free(temp);
	}
	// t_token	*print;

	// print = token_list;
	// printf("print: %s\n", print->str);
	// while (print->next != NULL)
	// {
	// 	print = print->next;
	// 	printf("print: %s\n", print->str);
	// }
	return(free_tokens(&token_list, temp, 0));
}




// PREVIOUS CODE


// #include "../../minishell.h"

// //TODO: ver cómo llamar esta funcion mejor

// // Quitar comillas, pasar tokens a lista, palabra por palabra
// // Quitar redirecciones de la lista (liberar esos nodos)
// // Quedarme con esos nodos y pasar a comandos 
// // Ojo con el string vacío ""


// /* 
// 	<< heredoc
// 	>> append
// 	> outfile
// 	< infile
// 	>| (Token >) OK, funciona como > 
// 	|> funciona como si le pasaras un proceso vacío (son dos tokens, | y >)
// 	|>> funciona como dos tokens, | - vacío - >>
// 	>>| ERROR
// 	<| ERROR
// 	<<| ERROR
// 	|<< ERROR
// 	|< ERROR
// 	>>> ERROR
// 	<<< Comportamiento indefinido, here-string, creo que no hay que gestionarlo -> Error ??
// 	*/
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

// void	new_outfile(t_redir **redir, char *red, char *doc)
// {
// 	printf("Entra al outfile???\n");
// 	t_redir	*head;
// 	t_redir	*node;

// 	if (!check_redirections(red))
// 	{
// 		printf("Me piro!\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	node = ft_calloc(sizeof(t_redir), 1);
// 	node->next = NULL;
// 	node->doc = doc;
// 	node->redir_type = GREAT;
// 	if (*redir == NULL)
// 		*redir = node;
// 	else
// 	{
// 		head = *redir;
// 		while ((*redir)->next != NULL)
// 			*redir = (*redir)->next;
// 		(*redir)->next = node;
// 		*redir = head;
// 	}
// 	printf("doc: %s\n", (*redir)->doc);
// }

// int	clean_process(t_parse **process_list, t_token **token_list)
// {
// 	t_parse	*new_node;
// 	t_token	*tmp;

// 	tmp = *token_list;
// 	new_node = init_process();
// 	printf("Entra en clean process\n");
// 	while (tmp->next != NULL)
// 	{
// 		if (!check_redirections(tmp->str))
// 		{
// 			printf("minishell: syntax error near unexpected token\n");
// 			return (0);
// 		}
// 		if (!ft_strcmp(tmp->str, ">"))
// 			new_outfile(&new_node->redirec, tmp->str, tmp->next->str);
// 		// else if (tmp->str[0] == '<' && tmp->str[1] != '<')
// 		// 	new_infile(&new_node->redirec, tmp->str, tmp->next->str);
// 		// else if (tmp->str[0] == '<' && tmp->str[1] == '<')
// 		// 	new_heredoc(&new_node->redirec, tmp->str, tmp->next->str);
// 		// else if (tmp->str[0] == '>' && tmp->str[1] == '>')
// 		// 	new_append(&new_node->redirec, tmp->str, tmp->next->str);
// 		// else if (tmp->str[0] == '|')
// 		// 	new_process(&new_node, tmp->str);
// 		printf("Token_List Head: %s\n", (*token_list)->str);
// 		printf("Token: %s\n", tmp->str);
// 		tmp = tmp->next;
// 	}
// 	return ;
// }

// void	parse_tokens(t_utils *utils, t_token **token_list)
// {
// 	t_parse	*process_list;

// 	process_list = NULL;
// 	printf("Entra en parse tokens\n");
// 	if(!clean_process(&process_list, token_list))
// 	{
// 		clear_token_list(token_list);
// 		return ;
// 	}
// }