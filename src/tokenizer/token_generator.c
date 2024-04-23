


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
t_parse	*init_process(void)
{
	t_parse	*process;

	process = ft_calloc(sizeof(t_parse), 1);
	if (!process)
		return (NULL); // O exit??
	process->cmd = NULL;
	process->built_in = 0;
	process->redirec = NULL;
	process->next = NULL;
	return (process);
}

void	new_outfile(t_redir **redir, char *red, char *doc)
{
	printf("Entra al outfile???\n");
	t_redir	*head;
	t_redir	*node;

	if (!check_redirections(red))
	{
		printf("Me piro!\n");
		exit(EXIT_FAILURE);
	}
	node = ft_calloc(sizeof(t_redir), 1);
	node->next = NULL;
	node->doc = doc;
	node->redir_type = GREAT;
	if (*redir == NULL)
		*redir = node;
	else
	{
		head = *redir;
		while ((*redir)->next != NULL)
			*redir = (*redir)->next;
		(*redir)->next = node;
		*redir = head;
	}
	printf("doc: %s\n", (*redir)->doc);
}

int	clean_process(t_parse **process_list, t_token **token_list)
{
	t_parse	*new_node;
	t_token	*tmp;

	tmp = *token_list;
	new_node = init_process();
	printf("Entra en clean process\n");
	while (tmp->next != NULL)
	{
		if (!check_redirections(tmp->str))
		{
			printf("minishell: syntax error near unexpected token\n");
			return (0);
		}
		if (!ft_strcmp(tmp->str, ">"))
			new_outfile(&new_node->redirec, tmp->str, tmp->next->str);
		// else if (tmp->str[0] == '<' && tmp->str[1] != '<')
		// 	new_infile(&new_node->redirec, tmp->str, tmp->next->str);
		// else if (tmp->str[0] == '<' && tmp->str[1] == '<')
		// 	new_heredoc(&new_node->redirec, tmp->str, tmp->next->str);
		// else if (tmp->str[0] == '>' && tmp->str[1] == '>')
		// 	new_append(&new_node->redirec, tmp->str, tmp->next->str);
		// else if (tmp->str[0] == '|')
		// 	new_process(&new_node, tmp->str);
		printf("Token_List Head: %s\n", (*token_list)->str);
		printf("Token: %s\n", tmp->str);
		tmp = tmp->next;
	}
	return ;
}

void	parse_tokens(t_utils *utils, t_token **token_list)
{
	t_parse	*process_list;

	process_list = NULL;
	printf("Entra en parse tokens\n");
	if(!clean_process(&process_list, token_list))
	{
		clear_token_list(token_list);
		return ;
	}
}